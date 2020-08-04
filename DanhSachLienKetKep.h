#pragma once
#include "Structure.h"
#include <iostream>

using namespace std;

void CreateList(ListVatTu& listVatTu);
bool Empty(ListVatTu& listVatTu);

void InsertFirst(ListVatTu& listVatTu, PTRVatTu& nodeTreeVatTu);
void InsertLast(ListVatTu& listVatTu, PTRVatTu& nodeTreeVatTu);
void InsertAfter(PTRVatTu2& p, PTRVatTu& nodeTreeVatTu);
PTRVatTu2 InsertOrder(ListVatTu& listVatTu, PTRVatTu& nodeTreeVatTu); //sap xep giam dan theo ma vat tu, tra ve node vua them

void DeleteFirst(ListVatTu& listVatTu);
void DeleteLast(ListVatTu& listVatTu);
void DeleteInfo(ListVatTu& listVatTu, char deleteMaVatTu[]);
