#include <stdio.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

struct RecordTypeNode {
    struct RecordType* data;
    struct RecordTypeNode* next;
};

// Fill out this structure
struct HashType
{
    struct RecordTypeNode* head;
};

void insert(struct HashType* this, int size, struct RecordType* value) 
{
    int index = hash(value->id, size);
    struct RecordTypeNode* node = malloc(sizeof(struct RecordTypeNode));
    node->data = value;
    node->next = NULL;

    if (this[index].head == NULL)
    {
        this[index].head = node;
    }
    else
    {
        node->next = this[index].head;
        this[index].head = node;
    }
}

// Compute the hash function
int hash(int x, int hashSize)
{
    return x % hashSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	for (int i = 0; i < hashSz; i++)
    {
        struct RecordTypeNode* elem = pHashArray[i].head;
        while (elem != NULL)
        {
            printf("index %d -> %d, %c, %d\n", i, elem->data->id, elem->data->name, elem->data->order);
            elem = elem->next;
        }
    }
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;
    int hashSz = 15;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
    struct HashType* arr = malloc(sizeof(struct HashType) * hashSz);
    for (int i = 0; i < hashSz; i++)
    {
        arr[i].head = NULL;
    }

    for (int i = 0; i < recordSz; i++) {
        insert(arr, hashSz, &pRecords[i]);
    }

    displayRecordsInHash(arr, hashSz);

    return 0;
}