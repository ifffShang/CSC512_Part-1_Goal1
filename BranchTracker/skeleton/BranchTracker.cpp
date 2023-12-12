#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <map>

using namespace llvm;

namespace {

struct BranchTrackerPass : public PassInfoMixin<BranchTrackerPass> {
  PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM) {
    std::map<std::string, std::tuple<std::string, int, int>> branchDictionary;
    int branchNumber = 0;

    for (Function &F : M) {
      LLVMContext &Ctx = F.getContext();
      FunctionCallee logFunction = setupLogFunction(F);

      for (BasicBlock &B : F) {
        processBasicBlock(B, branchDictionary, branchNumber, logFunction);
      }

      if (!branchDictionary.empty()) {
        printFunctionInfo(F);
      }
    }

    printBranchDictionary(branchDictionary);
    return PreservedAnalyses::all();
  }

private:
  FunctionCallee setupLogFunction(Function &F) {
    LLVMContext &Ctx = F.getContext();
    Type *voidType = Type::getVoidTy(Ctx);
    Type *charPointerType = Type::getInt8PtrTy(Ctx);
    FunctionType *logFuncType = FunctionType::get(voidType, {charPointerType}, false);
    return F.getParent()->getOrInsertFunction("logBranchActivity", logFuncType);
  }

void processBasicBlock(BasicBlock &B, std::map<std::string, std::tuple<std::string, int, int>> &branchDictionary, int &branchNumber, FunctionCallee logFunction) {
    for (Instruction &I : B) {
        if (auto *BI = dyn_cast<BranchInst>(&I)) {
            if (BI->isConditional()) {
                const DebugLoc &Loc = BI->getDebugLoc();

                if (Loc) {
                    // Retrieve the Module object from the BasicBlock
                    Module *M = B.getParent()->getParent();
                    // Get the source file name from the Module
                    std::string sourceFileName = M->getSourceFileName();
                    std::string opcodeName = BI->getOpcodeName();
                    int startLine = Loc.getLine();

                    for (int i = 0; i < BI->getNumSuccessors(); ++i) {
                        BasicBlock *branch = BI->getSuccessor(i);
                        std::string branchID = opcodeName + "_" + std::to_string(branchNumber);

                        int targetLine = branch->getFirstNonPHI()->getDebugLoc().getLine();
                        branchDictionary[branchID] = std::make_tuple(sourceFileName, startLine, targetLine);
                        branchNumber++;

                        IRBuilder<> builder(&*branch->getFirstInsertionPt());
                        builder.CreateCall(logFunction, {builder.CreateGlobalStringPtr(branchID)});
                    }
                }
            }
        }
    }
}


  void printFunctionInfo(const Function &F) {
    errs() << "Function: " << F.getName() << " - Address: " << &F << "\n";
  }

  void printBranchDictionary(const std::map<std::string, std::tuple<std::string, int, int>> &branchDictionary) {
    errs() << "Branch Dictionary:\n";
    for (const auto &[branchID, info] : branchDictionary) {
      errs() << branchID << ": File " << std::get<0>(info) << ", Lines "
             << std::get<1>(info) << " to " << std::get<2>(info) << "\n";
    }
  }
};

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {
    .APIVersion = LLVM_PLUGIN_API_VERSION,
    .PluginName = "Branch Tracker",
    .PluginVersion = "1.0",
    .RegisterPassBuilderCallbacks = [](PassBuilder &PB) {
      PB.registerPipelineStartEPCallback(
        [](ModulePassManager &MPM, OptimizationLevel Level) {
          MPM.addPass(BranchTrackerPass());
        });
    }
  };
}

} // namespace


