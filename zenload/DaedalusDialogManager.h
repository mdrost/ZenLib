#pragma once
#include <vector>
#include <string>
#include <functional>
#include <set>
#include "zCCSLib.h"
#include "DaedalusGameState.h"

namespace ZenLoad
{
    class DaedalusVM;
    struct oCMsgConversationData;
}

namespace GameState
{
    class DaedalusDialogManager
    {
    public:
        DaedalusDialogManager(ZenLoad::DaedalusVM& vm, const std::string& ou_bin);

        /**
         * Registers the externals used for dialog-processing
         * @param onAIOutput Callback in case an NPC is saying something (self, target, message)
         */
        void registerExternals(std::function<void(NpcHandle, NpcHandle, const ZenLoad::oCMsgConversationData&)> onAIOutput,
            std::function<void(NpcHandle, std::vector<InfoHandle>)> onStartConversation);

        /**
         * Sets the given info-instance as "known" to the given NPC-Instance
         */
        void setNpcInfoKnown(size_t npcInstance, size_t infoInstance);
    private:

        /**
         * Gathers all C_Info-Instances and puts them into m_NpcInfosByNpcSymbols
         */
        void gatherNpcInformation();

        /**
         * Message library
         */
        ZenLoad::zCCSLib m_MessageLib;

        /**
         * Callback in case an NPC is saying something (self, target, message)
         */
        std::function<void(NpcHandle, NpcHandle, const ZenLoad::oCMsgConversationData&)> m_OnAIOutput;

        /**
         * Current daedalus VM
         */
        ZenLoad::DaedalusVM& m_VM;

        /**
         * Map of NPC-Sym-Handles and their C_Infos
         */
        std::map<size_t, std::vector<InfoHandle>> m_NpcInfosByNpcSymbols;
        std::map<size_t, std::set<size_t>> m_KnownNpcInfoSymbolsByNpcSymbols;
    };
}