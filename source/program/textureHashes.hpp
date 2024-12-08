#include <stdexcept>
// Helper macros to print the value of a macro at compile-time
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define PRINT_MACRO_AT_COMPILE_TIME(var) #var "=`" VALUE(var) "`"

struct hashTable {
	uint64_t hash;
	uint16_t fileID;
	uint8_t bytesPerPixel;
	uint8_t swizzleExpand;
	uint8_t swizzleType;
};

template <typename T> constexpr uint64_t has_duplicates(const T *array, std::size_t size)
{
	for (std::size_t i = 1; i < size; i++)
		for (std::size_t j = 0; j < i; j++)
			if (array[i].hash == array[j].hash) {
				return array[i].hash;
			}
	return 0;
}

constexpr hashTable TEXTURE_HASHES_0[] = {
	{0x63ABF4F4F3EB25A2lu, 0, 16, 4, 3},
	{0xBA7231B0E759A03Elu, 1, 16, 4, 3},
	{0xA32312BDE3517954lu, 4, 16, 4, 3},
	{0xB74E06681F95BE4Alu, 5, 16, 4, 3},
	{0, 0, 0, 0, 0}
};

constexpr hashTable TEXTURE_HASHES_1[] = {
	{0x6662A711FC9D6530lu, 2, 16, 4, 3},
	{0x5122BD8AA08DD18Clu, 4, 16, 4, 3},
	{0xF5990FFFF815E897lu, 5, 16, 4, 3},
	{0x22067551C0119FB2lu, 6, 16, 4, 3},
	{0x1EE686BBF12BBAC5lu, 7, 16, 4, 3},
	{0x53EA3F4D2E94CB2Blu, 16, 16, 4, 3},
	{0x80A63F4C00673E28lu, 21, 16, 4, 3},
	{0x4BC3BC7130BE8785lu, 22, 16, 4, 3},
	{0xD4C67151A9EE26C4lu, 23, 16, 4, 3},
	{0xF7BA307B2C85E131lu, 24, 16, 4, 3},
	{0xF7C9B8F486C7434Clu, 25, 16, 4, 3},
	{0x5A788987946AF8A7lu, 26, 16, 4, 3},
	{0x67341C8D4FF71123lu, 27, 16, 4, 3},
	{0x35A0BBD0DE77CE2Alu, 28, 16, 4, 3},
	{0x864FEC17B06CC4ADlu, 29, 16, 4, 3},
	{0x891AE5A7F49B98BBlu, 30, 16, 4, 3},
	{0x9E4EFB1C8570E8CAlu, 31, 16, 4, 3},
	{0x110B4BF141304E92lu, 34, 16, 4, 3},
	{0x4BD88568F75275EDlu, 36, 16, 4, 3},
	{0xD2A678BB6286F898lu, 37, 16, 4, 3},
	{0x6003C5993AE3DDFAlu, 44, 16, 4, 3},
	{0xAD65DFA7669CFB97lu, 45, 16, 4, 3},
	{0xC452E9C10E68FEE3lu, 51, 16, 4, 3},
	{0x3EBF4E11214C5FEClu, 54, 16, 4, 3},
	{0x861000A4D368229Alu, 57, 16, 4, 3},
	{0xFF2D84D63FBB1078lu, 59, 16, 4, 3},
	{0xADFB8267EDCE38D1lu, 60, 16, 4, 3},
	{0x9CACE41F3AF01F91lu, 64, 16, 4, 3},
	{0xFD8AF294FEEE47BClu, 66, 16, 4, 3},
	{0x6C4CF72A1271C3FFlu, 67, 16, 4, 3},
	{0xF5E92EE782D33871lu, 68, 16, 4, 3},
	{0x61D4EE7070000A88lu, 70, 16, 4, 3},
	{0x0DC72037B78738BBlu, 71, 16, 4, 3},
	{0x5312D0C9FB2AB711lu, 72, 16, 4, 3},
	{0xDE91D1071605EB4Elu, 73, 16, 4, 3},
	{0x2EF9B52D4E1D0DBBlu, 75, 16, 4, 3},
	{0x1F5E5A6D86E8982Blu, 76, 16, 4, 3},
	{0x9231CCBC1EFCF436lu, 79, 16, 4, 3},
	{0x1703660C26CC0E7Clu, 80, 16, 4, 3},
	{0x8B68A5DBFB989FE8lu, 83, 16, 4, 3},
	{0x475C50B0B0E5FC69lu, 87, 16, 4, 3},
	{0x6D1FE542270A6EF4lu, 88, 16, 4, 3},
	{0x50760DD285A09239lu, 98, 16, 4, 3},
	{0x252A821C7A1716CFlu, 112, 16, 4, 3},
	{0x667CF6D65132406Alu, 113, 16, 4, 3},
	{0xCD76785719AA989Alu, 114, 16, 4, 3},
	{0x53F0FC250F31972Elu, 120, 4, 3, 4},
	{0xCF06D25C5FC9CB32lu, 121, 16, 4, 3},
	{0x958C8D5E8B499C43lu, 123, 16, 4, 3},
	{0x72D6F8E329EC9BD3lu, 124, 16, 4, 3},
	{0x674913F3564C8555lu, 125, 16, 4, 3},
	{0x1F170DD711AD7F43lu, 126, 16, 4, 3},
	{0x122530663699AC71lu, 127, 16, 4, 3},
	{0xD8F60C065DBD152Flu, 128, 16, 4, 3},
	{0xA32312BDE3517954lu, 130, 16, 4, 3},
	{0x147689E77E4404B9lu, 131, 16, 4, 3},
	{0xF26BC2F8CF39FDBDlu, 132, 16, 4, 3},
	{0x0DF9AE7EBFD0B191lu, 135, 16, 4, 3},
	{0x896EBCD5FFEF7CF3lu, 136, 16, 4, 3},
	{0xFC97D4D3C21861A8lu, 146, 16, 4, 3},
	{0x71767AB2CFE860DBlu, 147, 16, 4, 3},
	{0, 0, 0, 0, 0}
};

static_assert(!has_duplicates(TEXTURE_HASHES_0, std::size(TEXTURE_HASHES_0)), "Detected repeated hash in TEXTURE_HASHES_0!");
static_assert(!has_duplicates(TEXTURE_HASHES_1, std::size(TEXTURE_HASHES_1)), "Detected repeated hash in TEXTURE_HASHES_1!");

auto compareHashes0(uint64_t hashToCompare) {
	for(size_t i = 0; i < std::size(TEXTURE_HASHES_0); i++)
		if (TEXTURE_HASHES_0[i].hash == hashToCompare) 
			return TEXTURE_HASHES_0[i];
	return TEXTURE_HASHES_0[std::size(TEXTURE_HASHES_0) - 1];
}

auto compareHashes1(uint64_t hashToCompare) {
	for(size_t i = 0; i < std::size(TEXTURE_HASHES_1); i++)
		if (TEXTURE_HASHES_1[i].hash == hashToCompare) 
			return TEXTURE_HASHES_1[i];
	return TEXTURE_HASHES_1[std::size(TEXTURE_HASHES_1) - 1];
}