#pragma once
#include"Structure.h"
#include <iostream>

using namespace std;

void CreateTree(PTRVatTu& root);
bool Empty(PTRVatTu root);
void InsertTree(PTRVatTu& p, char addKey, VatTu addVatTu);
void DeleteTree(PTRVatTu& p, char deleteVatTu);
void DeleteTreeCase3(PTRVatTu& p, PTRVatTu& temp);

