// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
	uint8_t addr[16];
	uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
	// It'll only connect to one or two seed nodes because once it connects,
	// it'll get a pile of addresses with newer timestamps.
	// Seed nodes are given a random 'last seen time' of between one and two
	// weeks ago.
	const int64_t nOneWeek = 7 * 24 * 60 * 60;
	for (unsigned int k = 0; k < count; ++k)
	{
		struct in_addr ip;
		unsigned int i = data[k], t;

		// -- convert to big endian
		t = (i & 0x000000ff) << 24u
			| (i & 0x0000ff00) << 8u
			| (i & 0x00ff0000) >> 8u
			| (i & 0xff000000) >> 24u;

		memcpy(&ip, &t, sizeof(ip));

		CAddress addr(CService(ip, port));
		addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
		vSeedsOut.push_back(addr);
	}
}

class CMainParams : public CChainParams {
public:
	CMainParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x5f;
		pchMessageStart[1] = 0x79;
		pchMessageStart[2] = 0x64;
		pchMessageStart[3] = 0xc9;
		vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
		nDefaultPort = 44144;
		nRPCPort = 44155;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		/* The initial difficulty after switching to NeoScrypt (0.0625) */
		bnNeoScryptFirstTarget = CBigNum(~uint256(0) >> 28);

		// Build the genesis block. Note that the output of the genesis coinbase cannot
		// be spent as it did not originally exist in the database.

		const char* pszTimestamp = "Tens of millions of dollars in recent weeks have poured into the coffers";
		std::vector<CTxIn> vin;
		vin.resize(1);
		vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
		std::vector<CTxOut> vout;
		vout.resize(1);
		vout[0].SetEmpty();
		CTransaction txNew(1, 1529903627, vin, vout, 0);
		genesis.vtx.push_back(txNew);
		genesis.hashPrevBlock = 0;
		genesis.hashMerkleRoot = genesis.BuildMerkleTree();
		genesis.nVersion = 1;
		genesis.nTime = 1529903627; //
		genesis.nBits = 0x1d00ffff;
		genesis.nNonce = 2325781908;

		// printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); 
		// printf("genesis.hashMerkleRoot = %s \n", genesis.hashMerkleRoot.ToString().c_str()); 


		hashGenesisBlock = genesis.GetHash();

		assert(genesis.hashMerkleRoot == uint256("0xccc72c7aa635f43f4a23e1d55e37a1dc4b670079d88f7e22521aa95606083c70"));
		assert(hashGenesisBlock == uint256("0x1d1672a056d81436643962829296893d43a28124ed046896f35bb0b1c01030c1"));


		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 130); // u
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 39); // G
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 138); // x
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 76); // X
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0x06)(0x2D).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();


		vSeeds.push_back(CDNSSeedData("node1",  "104.237.136.27"));
		vSeeds.push_back(CDNSSeedData("node2",  "66.228.54.99"));

		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

		nPoolMaxTransactions = 3;
		//strSporkKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
		//strMasternodePaymentsPubKey = "046f78dcf911fbd61910136f7f0f8d90578f68d0b3ac973b5040fb7afb501b5939f39b108b0569dca71488f5bbf498d92e4d1194f6f941307ffd95f75e76869f0e";
		strDarksendPoolDummyAddress = "udoFpv9LEL3JCN6JKQsWhPjRT8vu3LKRKm";
		nLastPOWBlock = 100000000000000;
		nPOSStartBlock = 1;
	}


	virtual const CBlock& GenesisBlock() const { return genesis; }
	virtual Network NetworkID() const { return CChainParams::MAIN; }

	virtual const vector<CAddress>& FixedSeeds() const {
		return vFixedSeeds;
	}
protected:
	CBlock genesis;
	vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
	CTestNetParams() {
		// The message start string is designed to be unlikely to occur in normal data.
		// The characters are rarely used upper ASCII, not valid as UTF-8, and produce
		// a large 4-byte int at any alignment.
		pchMessageStart[0] = 0x1d;
		pchMessageStart[1] = 0x7e;
		pchMessageStart[2] = 0xa6;
		pchMessageStart[3] = 0x2c;
		bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
		bnNeoScryptFirstTarget = CBigNum(~uint256(0) >> 20);
		vAlertPubKey = ParseHex("042a4acc6f2c09d425e45c73b11e8f5c2afefdab644689948dbe3e7efbd32bfe8a810ed0532359f42f6a15830137c28d10504056cb64539e5fea5f9ed1dc62aa2b");
		nDefaultPort = 33133;
		nRPCPort = 33155;
		strDataDir = "testnet";

		// Modify the testnet genesis block so the timestamp is valid for a later start.
		genesis.nBits = 0x1d00ffff;
		genesis.nNonce = 2325781908;	


		//printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str()); 

		assert(hashGenesisBlock == uint256("0x1d1672a056d81436643962829296893d43a28124ed046896f35bb0b1c01030c1"));

		vFixedSeeds.clear();
		vSeeds.clear();

		base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
		base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 38);
		base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 88);
		base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1, 98);
		base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
		base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

		convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

		nLastPOWBlock = 0x7fffffff;
	}
	virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
	return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
	switch (network) {
	case CChainParams::MAIN:
		pCurrentParams = &mainParams;
		break;
	case CChainParams::TESTNET:
		pCurrentParams = &testNetParams;
		break;
	default:
		assert(false && "Unimplemented network");
		return;
	}
}

bool SelectParamsFromCommandLine() {

	fTestNet = GetBoolArg("-testnet", false);

	if (fTestNet) {
		SelectParams(CChainParams::TESTNET);
	}
	else {
		SelectParams(CChainParams::MAIN);
	}
	return true;
}
