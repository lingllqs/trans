#include "ecdict.h"
#include "test.h"


int main(void)
{
	Entry e;

	ASSERT(ecdict_lookup("data/ecdict.csv", "apple", &e));
	ASSERT(e.word);
	ASSERT(e.definition);
	ASSERT(e.translation);

	return 0;
}
