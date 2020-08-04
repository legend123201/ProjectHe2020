#pragma once
#include"Structure.h"
#include <iostream>

using namespace std;

void CreateTree(PTRVatTu& root);
bool Empty(PTRVatTu root);

PTRVatTu InsertTree(PTRVatTu& p, char addKey[], VatTu addVatTu);
void DeleteTree(PTRVatTu& p, char deleteKey[], char maVatTuThayDoiVungNho[]);
void DeleteTreeCase3(PTRVatTu& p, PTRVatTu& temp, char maVatTuThayDoiVungNho[]);

PTRVatTu TimKiemVatTu(PTRVatTu root, char findKey[]);
