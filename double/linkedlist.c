// Sopian Version Linked List

#include <limits.h>
#include <malloc.h>
#include "linkedlist.h"

/********** BODY SUB PROGRAM *******/
/******** Predikat untuk test keadaan LIST ****/

boolean ListEmpty(List L) {
    return (First(L) == Nil);
}

/******** Konstruktor/Kreator List Kosong ****/

void CreateList(List *L) {
    First(*L) = Nil;
}

/******** Manajemen Memory ****/

address Alokasi(infotype X) {
    address P;
    P = (address)malloc(sizeof(ElmtList));
    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
    }
    return P;
}

void DeAlokasi(address P) {
    if (P != Nil) {
        free(P);
    }
}

/**** Pencarian sebuah elemen List ***/

address Search(List L, infotype X) {
    address P;
    boolean found = false;
    P = First(L);
    while ((P != Nil) && (!found)) {
        if (Info(P) == X) {
            found = true;
        } else {
            P = Next(P);
        }
    }
    return P;
}

boolean FSearch(List L, address P) {
    boolean found = false;
    address PSearch;
    PSearch = First(L);
    while ((PSearch != Nil) && (!found)) {
        if (PSearch == P) {
            found = true;
        } else {
            PSearch = Next(PSearch);
        }
    }
    return found;
}

address SearchPrec(List L, infotype X) {
    address Prec, P;
    boolean found = false;
    Prec = Nil;
    P = First(L);
    while ((P != Nil) && (!found)) {
        if (Info(P) == X) {
            found = true;
        } else {
            Prec = P;
            P = Next(P);
        }
    }
    if (found) {
        return Prec;
    } else {
        return Nil;
    }
}

/***** PRIMITIF BERDASARKAN NILAI ****/

/***** Penambahan Elemen ****/

void InsVFirst(List *L, infotype X) {
    address P;
    P = Alokasi(X);
    if (P != Nil) {
        InsertFirst(L, P);
    }
}

void InsVLast(List *L, infotype X) {
    address P;
    P = Alokasi(X);
    if (P != Nil) {
        InsertLast(L, P);
    }
}

/***** Penghapusan Elemen ****/

void DelVFirst(List *L, infotype *X) {
    address P;
    P = First(*L);
    *X = Info(P);
    First(*L) = Next(First(*L));
    DeAlokasi(P);
}

void DelVLast(List *L, infotype *X) {
    address PDel;
    PDel = First(*L);
    DelLast(L, &PDel);
    *X = Info(PDel);
    DeAlokasi(PDel);
}

/***** PRIMITIF BERDASARKAN ALAMAT ****/

/***** Penambahan elemen berdasarkan alamat ****/

void InsertFirst(List *L, address P) {
    Next(P) = First(*L);
    First(*L) = P;
}

void InsertAfter(List *L, address P, address Prec) {
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void InsertLast(List *L, address P) {
    address Last;
    if (First(*L) != Nil) {
        Last = First(*L);
        while (Next(Last) != Nil) {
            Last = Next(Last);
        }
        Next(Last) = P;
    } else {
        First(*L) = P;
    }
}

/***** Penghapusan sebuah elemen ****/

void DelFirst(List *L, address *P) {
    *P = First(*L);
    First(*L) = Next(First(*L));
}

void DelP(List *L, infotype X) {
    address P, Prec;
    boolean found = false;
    Prec = Nil;
    P = First(*L);
    while ((P != Nil) && (!found)) {
        if (Info(P) == X) {
            found = true;
        } else {
            Prec = P;
            P = Next(P);
        }
    }
    if (found) {
        if (Prec == Nil && Next(P) == Nil) {
            First(*L) = Nil;
        } else if (Prec == Nil) {
            First(*L) = Next(P);
        } else {
            Next(Prec) = Next(P);
        }
        Next(P) = Nil;
        DeAlokasi(P);
    }
}

void DelLast(List *L, address *P) {
    address Prec;
    *P = First(*L);
    Prec = Nil;
    while (Next(*P) != Nil) {
        Prec = *P;
        *P = Next(*P);
    }
    if (Prec == Nil) {
        First(*L) = Nil;
    } else {
        Next(Prec) = Nil;
    }
}

void DelAfter(List *L, address *Pdel, address Prec) {
    *Pdel = Next(Prec);
    if (*Pdel != Nil) {
        Next(Prec) = Next(*Pdel);
        Next(*Pdel) = Nil;
    }
}

/***** PROSES SEMUA ELEMEN LIST ****/

void PrintInfo(List L) {
    address P;
    if (First(L) == Nil) {
        printf("List Kosong .... \a\n");
    } else {
        P = First(L);
        for (;;) {
            if (P == Nil) {
                printf("\n");
                break;
            } else {
                printf("%d ", Info(P));
                P = Next(P);
            }
        }
    }
}

int NbElmt(List L) {
    int Jml = 0;
    address P;
    if (First(L) != Nil) {
        P = First(L);
        for (;;) {
            if (P == Nil) {
                break;
            } else {
                Jml++;
                P = Next(P);
            }
        }
    }
    return Jml;
}

infotype Max(List L) {
    int Maks = INT_MIN;
    address P;
    if (First(L) != Nil) {
        P = First(L);
        for (;;) {
            if (P == Nil) {
                break;
            } else {
                if (Maks < Info(P)) {
                    Maks = Info(P);
                }
                P = Next(P);
            }
        }
    }
    return Maks;
}

address AdrMax(List L) {
    address P;
    infotype X;
    X = Max(L);
    if (X != INT_MIN) {
        P = Search(L, X);
    } else {
        P = Nil;
    }
    return P;
}

infotype Min(List L) {
    int Minimal = INT_MAX;
    address P;
    if (First(L) != Nil) {
        P = First(L);
        for (;;) {
            if (P == Nil) {
                break;
            } else {
                if (Minimal > Info(P)) {
                    Minimal = Info(P);
                }
                P = Next(P);
            }
        }
    }
    return Minimal;
}

address AdrMin(List L) {
    address P;
    infotype X;
    X = Min(L);
    if (X != INT_MAX) {
        P = Search(L, X);
    } else {
        P = Nil;
    }
    return P;
}

infotype Average(List L) {
    int Jml = 0;
    int Acc = 0;
    address P;
    if (First(L) != Nil) {
        P = First(L);
        for (;;) {
            if (P == Nil) {
                break;
            } else {
                Acc = Acc + Info(P);
                Jml++;
                P = Next(P);
            }
        }
    }
    if (Jml > 0) {
        Jml = (int)Acc / Jml;
    }
    return Jml;
}

/********** PROSES TERHADAP LIST ********/
/********** ******************* **********/

void DelAll(List *L) {
    address PDel;
    PDel = First(*L);
    while (PDel != Nil) {
        DelFirst(L, &PDel);
        DeAlokasi(PDel);
        PDel = First(*L);
    }
}

void InversList(List *L) {
    address P, PNew;
    List Temp;
    CreateList(&Temp);
    P = First(*L);
    while (P != Nil) {
        PNew = P;
        P = Next(P);
        First(*L) = P;
        Next(PNew) = Nil;
        InsertFirst(&Temp, PNew);
    }
    First(*L) = First(Temp);
}

List FInversList(List L) {
    int Jml;
    List Temp;
    infotype X;
    boolean gagal = false;
    address P;
    CreateList(&Temp);
    P = First(L);
    while ((P != Nil) && (!gagal)) {
        Jml = NbElmt(Temp);
        X = Info(P);
        InsVFirst(&Temp, X);
        if (Jml != NbElmt(Temp)) {
            P = Next(P);
        } else {
            gagal = true;
        }
    }
    if (gagal) {
        DelAll(&Temp);
    }
    return Temp;
}

void CopyList(List L1, List *L2) {
    CreateList(L2);
    First(*L2) = First(L1);
}

List FCopyList(List L) {
    int Jml;
    infotype X;
    List Temp;
    boolean gagal = false;
    address P;
    CreateList(&Temp);
    P = First(L);
    while ((P != Nil) && (!gagal)) {
        Jml = NbElmt(Temp);
        X = Info(P);
        InsVLast(&Temp, X);
        if (Jml != NbElmt(Temp)) {
            P = Next(P);
        } else {
            gagal = true;
        }
    }
    if (gagal) {
        DelAll(&Temp);
    }
    return Temp;
}

void CpAlokList(List Lin, List *Lout) {
    boolean berhasil = true;
    address P, PNew;
    infotype X;
    CreateList(Lout);
    P = First(Lin);
    while ((P != Nil) && (berhasil)) {
        X = Info(P);
        PNew = Alokasi(X);
        if (PNew != Nil) {
            InsertLast(Lout, PNew);
            P = Next(P);
        } else {
            berhasil = false;
        }
    }
    if (!berhasil) {
        DelAll(Lout);
    }
}

void Konkat(List L1, List L2, List *L3) {
    boolean L1_ada = false;
    boolean gagal = false;
    infotype X;
    address P, PNew;
    if (!ListEmpty(*L3)) {
        DelAll(L3);
    }
    if (!ListEmpty(L1)) {
        L1_ada = true;
        CpAlokList(L1, L3);
        if (First(*L3) == Nil) {
            gagal = true;
        }
    }
    if (!ListEmpty(L2) && (!gagal)) {
        if (L1_ada) {
            P = First(L2);
            while ((P != Nil) && (!gagal)) {
                X = Info(P);
                PNew = Alokasi(X);
                if (PNew != Nil) {
                    InsertLast(L3, PNew);
                    P = Next(P);
                } else {
                    gagal = false;
                }
            }
        } else {
            CpAlokList(L2, L3);
            if (First(*L3) == Nil) {
                gagal = true;
            }
        }
    }
    if (gagal) {
        DelAll(L3);
    }
}

void Konkat1(List *L1, List *L2, List *L3) {
    address P, P_L3;
    if (!ListEmpty(*L3)) {
        DelAll(L3);
    }
    if (!ListEmpty(*L1)) {
        First(*L3) = First(*L1);
        First(*L1) = Nil;
    }
    if (!ListEmpty(*L2)) {
        P = First(*L2);
        InsertLast(L3, P);
        First(*L2) = Nil;
    }
}

void PecahList(List *L1, List *L2, List L) {
    int Jml, i;
    address P;
    boolean gagal = false;
    infotype X;
    if (First(L) != Nil) {
        CreateList(L1);
        P = First(L);
        i = 1;
        while ((i <= NbElmt(L) / 2) && (!gagal)) {
            Jml = NbElmt(*L1);
            X = Info(P);
            InsVLast(L1, X);
            if (Jml != NbElmt(*L1)) {
                P = Next(P);
                i++;
            } else {
                gagal = true;
            }
        }
        if (!gagal) {
            CreateList(L2);
            while ((P != Nil) && (!gagal)) {
                Jml = NbElmt(*L2);
                X = Info(P);
                InsVLast(L2, X);
                if (Jml != NbElmt(*L2)) {
                    P = Next(P);
                } else {
                    gagal = true;
                }
            }
        }
        if (gagal) {
            DelAll(L1);
            DelAll(L2);
        }
    }
}
