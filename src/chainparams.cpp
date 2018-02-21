
// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
static Checkpoints::MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0xd880c4e8db4427c936d8c759b463102694366b3e2e512f7b62a946c0d39d50dd"))
        ( 333, uint256("0x52d72726edd411314324d36b2c9da463bfd6a17f7951581716b1333ee86f91af"))
        ( 5000, uint256("0x902948114a142409d9a762268cf3626f714e1f2737d27ea8f52be66a29c254d0"))
        ( 8600, uint256("0x9eeed680fb1667eb91ed41f79e5fe1ec4a587b68a3f5e3f39b417db5281f89db"))
        ( 11500, uint256("0x0fec696fb054596450f799ba1e68a3b699bbf74dc8e10d62d0c9687e6cb339ff"))
        ( 15500, uint256("0xf95b1982e83c898259bd790f184b98f56034a06cdd51a6849e40aceb0e1382ae"))
        ( 20500, uint256("0x4f9f09339e631faace8c76f03f9cdca9fdefbc6b31ffea77dccb4dc56e12dbde"))
        ( 24033, uint256("0x1eea2ef5f8df6825d63f9c1253e962aeb3031476128fae8e90408ce0885f799e"))
        ( 59650, uint256("0x799ee1d88c218495454c14a96605d2781a3b6615c918d5dd5123479383b30a9b"))
        
        ;
static const Checkpoints::CCheckpointData data = {
        &mapCheckpoints,
        //1512803778, // * UNIX timestamp of last checkpoint block
        //40093,   // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        //750     // * estimated number of transactions per day after checkpoint
    };

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        ( 0, uint256("0xd880c4e8db4427c936d8c759b463102694366b3e2e512f7b62a946c0d39d50dd"))
        ;
static const Checkpoints::CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        //1503261995,
        //0,
        //250
    };

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("0xd880c4e8db4427c936d8c759b463102694366b3e2e512f7b62a946c0d39d50dd"))
        ;
static const Checkpoints::CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };

class CMainParams : public CChainParams {
public:
    CMainParams() {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /** 
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xf1;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0xa4;
        pchMessageStart[3] = 0xdc;

        vAlertPubKey = ParseHex("");
        nDefaultPort = 21524;
        bnProofOfWorkLimit = ~uint256(0) >> 20;
        nSubsidyHalvingInterval = 900000;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 20 * 60; // 20 minutes
        nTargetSpacing = 1 * 65; // 65 Seconds

        const char* pszTimestamp = "15/11/2017 Boxy Launch -ARTAX Implemented-";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 30 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("215284710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1510723234;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 1572978;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xd880c4e8db4427c936d8c759b463102694366b3e2e512f7b62a946c0d39d50dd"));
        assert(genesis.hashMerkleRoot == uint256("0xcbbd3ac705fc543c0a61193ab593d9abecdf8abdfe8695cfb017232982b0bb26"));

        vSeeds.push_back(CDNSSeedData("boxycoin.org", "159.203.161.244"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "138.68.174.82"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "104.131.44.238"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "138.68.191.238"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "178.62.57.88"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "boxy.online"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "pool.boxy.online"));
        vSeeds.push_back(CDNSSeedData("boxycoin.org", "electrum.boxy.online"));
        

        base58Prefixes[PUBKEY_ADDRESS] = list_of(75);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(18);
        base58Prefixes[SECRET_KEY] =     list_of(203);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "045fdc1d5796a4cc3ec7b93de854747f91ac8c44b150a37a45fe7b115e19463f902639ac385a7262423d5ac2e5fcea81a403525b25e56c6ff6d6020ff97b9bff57";
        strMasternodePaymentsPubKey = "049484542a6a421df34eec30f83b59cdc6ba468fe8d5a306faddb600ceb5b5cfe612eedad016275a0caf5c9c0db69974de9fc6127c74bc69768329c4ff9522c1cf";
        strDarksendPoolDummyAddress = "Xq19GqFvajRrEdDHYRKGYjTsQfpV5jyipF";
        nStartMasternodePayments = 1519465554; //24 Feb 2018 20:36:16 GMT
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x18;
        pchMessageStart[3] = 0x5e;

        vAlertPubKey = ParseHex("04cdf672c7d3f41df30d4ab30ff31ecf3b06349268978bb68ec71274ee7174179f68fae44ae777ceee5bdbd21f0449aeb9ffe8a6f6b86628b041be20952b6884c9");
        nDefaultPort = 21528;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 20 * 60; // 10 minutes
        nTargetSpacing = 1 * 60; // 1 minute

        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1510723234;
        genesis.nNonce = 1572978;
        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0xd880c4e8db4427c936d8c759b463102694366b3e2e512f7b62a946c0d39d50dd"));

        vFixedSeeds.clear();
        vSeeds.clear();
        

        base58Prefixes[PUBKEY_ADDRESS] = list_of(75);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(18);
        base58Prefixes[SECRET_KEY]     = list_of(203);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
        strDarksendPoolDummyAddress = "X1EZuxhhNMAUofTBEeLqGE1bJrpC2TWRNp";
        nStartMasternodePayments = 1519465554; //December 16, 2017 12:00:00 AM GMT+00:00
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xc3;
        pchMessageStart[2] = 0x18;
        pchMessageStart[3] = 0x5e;

        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 10 * 60; // 10 minutes
        nTargetSpacing = 1 * 65; // 65 seconds
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1510723234;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1572978;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 21529;
        assert(hashGenesisBlock == uint256("0xd880c4e8db4427c936d8c759b463102694366b3e2e512f7b62a946c0d39d50dd"));

        vFixedSeeds.clear(); //! Regtest mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Regtest mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams {
public:
    CUnitTestParams() {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 18445;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();  //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const 
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval)  { nSubsidyHalvingInterval=anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority)  { nEnforceBlockUpgradeMajority=anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority)  { nRejectBlockOutdatedMajority=anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority)  { nToCheckBlockUpgradeMajority=anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks)  { fDefaultConsistencyChecks=afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) {  fAllowMinDifficultyBlocks=afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};
static CUnitTestParams unitTestParams;


static CChainParams *pCurrentParams = 0;

CModifiableParams *ModifiableParams()
{
   assert(pCurrentParams);
   assert(pCurrentParams==&unitTestParams);
   return (CModifiableParams*)&unitTestParams;
}

const CChainParams &Params() {
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams &Params(CBaseChainParams::Network network) {
    switch (network) {
        case CBaseChainParams::MAIN:
            return mainParams;
        case CBaseChainParams::TESTNET:
            return testNetParams;
        case CBaseChainParams::REGTEST:
            return regTestParams;
        case CBaseChainParams::UNITTEST:
            return unitTestParams;
        default:
            assert(false && "Unimplemented network");
            return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network) {
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
