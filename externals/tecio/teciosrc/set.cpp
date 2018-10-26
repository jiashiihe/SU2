#include "stdafx.h"
#include "MASTER.h"
 #define ___3500
#include "GLOBAL.h"
#include "TASSERT.h"
#include "ALLOC.h"
#include "SET.h"
 #define SetInitSize          (___2896(1,___3479))
 #define SetExpansionFactor   2
using tecplot::___4217; namespace { void ShiftSetForDelete(___3501 ___3476, ___3493 DeletePos); } namespace { ___3483* newSetData(___3493 ___2795) { REQUIRE(___2795 > 0 && ___2795 % ___3479 == 0); { return ___23(___2795 / ___3479, ___3483, "Set data"); } } } namespace { void deleteSetData(___3483* setData) { REQUIRE(VALID_REF(setData)); { ___1530(setData, "Set data"); } } } ___3501 ___29(___372 ___3574) { ___3501 ___3476 = ALLOC_ITEM(struct ___3502, "Set header"); if (___3476) { ___3476->size = SetInitSize; ___3476->data = newSetData(SetInitSize); if (___3476->data == NULL) ___939(&___3476); else ___493(___3476); } if ((___3476 == NULL) && ___3574) {
 #if defined(TECPLOTKERNEL)
 #if !defined UNITTEST
___1177(___4217("Out of memory for sets"));
 #endif
 #else
 #endif
} return ___3476; } void ___939(___3501 *___3476) { if (___3476 && *___3476) { if ((*___3476)->data) deleteSetData((*___3476)->data); ___1531(*___3476, "Set header"); *___3476 = NULL; } } ___372 ___3496(void       *___2098, ___90  ___494) { ___3501 *SetRef = (___3501 *)___2098; REQUIRE(VALID_REF(SetRef)); REQUIRE(VALID_REF(*SetRef) || *SetRef == NULL); ___4278(___494); if (*SetRef != NULL) ___939(SetRef); ENSURE(*SetRef == NULL); return ___4226; } namespace { void copySetData( ___3483*       targetSetData, ___3483 const* sourceSetData, ___3493       sourceSetSize) { { size_t sourceSetSizeInBytes = sizeof(sourceSetData[0]) * (sourceSetSize / ___3479); memcpy(targetSetData, sourceSetData, sourceSetSizeInBytes); } } } namespace { void initSetData( ___3483* setData, ___3493 startMember, ___3493 numMembers) { { size_t startOffsetInBytes = sizeof(setData[0]) * (startMember / ___3479); size_t numBytesToInit     = sizeof(setData[0]) * (numMembers / ___3479); memset(((char*)setData) + startOffsetInBytes, 0, numBytesToInit); } } } ___372 ___1201(___3501     ___3476, ___3493 max_val, ___372  ___3574) { ___3483  *data; ___3493  new_size; REQUIRE(max_val >= 0); if (!___3476) { if (___3574) {
 #if defined(TECPLOTKERNEL)
 #if !defined UNITTEST
___1177(___4217("Null Set expand"));
 #endif
 #else
 #endif
} return ___1305; } if (max_val <= ___3476->size) return ___4226; new_size = ___3476->size; while (new_size < max_val) new_size *= SetExpansionFactor; new_size = ___2896(new_size, ___3479); data = newSetData(new_size); if (!data) { if (___3574) {
 #if defined(TECPLOTKERNEL)
 #if !defined UNITTEST
___1177(___4217("Out of memory for sets"));
 #endif
 #else
 #endif
} return ___1305; } copySetData(data, ___3476->data, ___3476->size); initSetData(data, ___3476->size, (new_size - ___3476->size)); deleteSetData(___3476->data); ___3476->data = data; ___3476->size = new_size; return ___4226; } ___372 ___676(___3501    ___1121, ___3501    ___3656, ___372 ___3574) { if (___1121 && ___1121->data && ___3656 && ___3656->data && ___1201(___1121, ___3656->size, ___3574)) { copySetData(___1121->data, ___3656->data, ___3656->size); if (___1121->size > ___3656->size) initSetData(___1121->data, ___3656->size, (___1121->size - ___3656->size)); return ___4226; } else return ___1305; } ___372 ___83(___3501 ___1121, ___3501 ___3656, ___372 ___3574) { if (___1121 && ___1121->data && ___3656 && ___3656->data) { ___3493 ___2401; ___1472(___2401, ___3656) { if (!___17(___1121, ___2401, ___3574)) return ___1305; } return ___4226; } else return ___1305; } void ___493(___3501 ___3476) { if (___3476 && ___3476->data) initSetData(___3476->data, 0, ___3476->size); }
 #if defined USE_FUNCTIONS_FOR_SETS
___372 ___17(___3501     ___3476, ___3493 ___2401, ___372  ___3574) { REQUIRE(___2401 >= 0); if (___3476 && (___2401 + 1 <= ___3476->size || ___1201(___3476, ___2401 + 1, ___3574))) { ___3493 word = ___2401 / ___3479; ___3480 bit = (___3480)1 << (___2401 % ___3479); ___3476->data[word] |= bit; return ___4226; } else return ___1305; }
 #endif
void ___3334(___3501     ___3476, ___3493 ___2401) { REQUIRE(___2401 >= 0); if (___3476 && (___2401 < ___3476->size) && ___3476->data) { ___3493 word = ___2401 / ___3479; ___3480  bit = (___3480)1 << (___2401 % ___3479); ___3476->data[word] &= (((___3480)(-1)) ^ bit); } } void ___957(___3501     ___3476, ___3493 ___2402) { REQUIRE(VALID_REF(___3476)); REQUIRE(___2402 >= 0); ShiftSetForDelete(___3476, ___2402); } ___372 ___1955(___3501     ___3476, ___3493 ___2402, ___372  ___3571) { ___372  ___2040 = ___4226; ___3493 OrigLastMember; REQUIRE(VALID_REF(___3476)); OrigLastMember = ___1769(___3476, ___333); if (___2402 <= OrigLastMember) { ___2040 = ___1201(___3476, (OrigLastMember + 1) + 1, ___3571); ___3560(___3476, ___2402, OrigLastMember, 1); } if (___2040) ___2040 = ___17(___3476, ___2402, ___3571); ENSURE(VALID_BOOLEAN(___2040)); return ___2040; }
 #if defined USE_FUNCTIONS_FOR_SETS
___372 ___1956(___3501     ___3476, ___3493 ___2401) { if (___3476 && (0 <= ___2401 && ___2401 < ___3476->size)) { ___3493 word = ___2401 / ___3479; ___3480  bit = (___3480)1 << (___2401 % ___3479); return (___3476->data[word]&bit) != 0; } else return ___1305; }
 #endif
___372 ___2015(___3501 ___3476) { if (___3476 && ___3476->data) { ___3493 set_size_in_words = ___3476->size / ___3479; ___3493 word; for (word = 0; word < set_size_in_words; word++) { ___3480 word_val = ___3476->data[word]; if (word_val != 0) return ___1305; } } return ___4226; } ___372 ___1822(___3501 ___3476) { ___372  ___3359 = ___1305; ___3493 ContiguousMember = 0; ___3493 ___2402 = 0; REQUIRE(VALID_REF(___3476)); ___1472(___2402, ___3476) { if (___2402 == ContiguousMember) { ContiguousMember++; } else { ___3359 = ___4226; break; } } ENSURE(VALID_BOOLEAN(___3359)); return ___3359; } ___3493 ___2403(___3501 ___3476) { ___3493 count = 0; if (___3476 && ___3476->data) { ___3493 set_size_in_words = ___3476->size / ___3479; ___3493 word; for (word = 0; word < set_size_in_words; word++) { ___3480 word_val = ___3476->data[word]; while (word_val) { if (word_val&1) count++; word_val = word_val >> 1; } } } return count; } ___372 ___2033(___3501 ___3476) { ___3493 count = 0; if (___3476 && ___3476->data) { ___3493 set_size_in_words = ___3476->size / ___3479; for (___3493 word = 0; word < set_size_in_words; ++word) { ___3480 word_val = ___3476->data[word]; while (word_val) { if (word_val & 1) { if(++count > 1) return ___1305; } word_val = word_val >> 1; } } } return count == 1; }
 #if !defined UNITTEST
___3493 ___1761(___3501     ___3476, ___3493 ___3682) { ___3493 next_member = ___333; if (___3476 && ___3476->data) { ___3493 set_size_in_words = ___3476->size / ___3479; ___3493 word; ___3480 word_val = 0; int bit; if (___3682 == ___333) { word = 0; bit = 0; if (word < set_size_in_words) { word_val = ___3476->data[0]; } } else if (___3682 + 1 < ___3476->size) { word = (___3682 + 1) / ___3479; bit = static_cast<int>((___3682 + 1) % ___3479); if (word < set_size_in_words) { word_val = ___3476->data[word] >> bit; } } else { return ___333; } while ((word < set_size_in_words) && (word_val == 0)) { word++; bit = 0; if (word < set_size_in_words) { word_val = ___3476->data[word]; } } if (word < set_size_in_words) { while (!(word_val&1)) { word_val >>= 1; bit++; } next_member = word * ___3479 + bit; } } return next_member; }
 #endif
___3493 ___1769(___3501     ___3476, ___3493 ___3682) { ___3493 next_member = ___333; if (___3476 && ___3476->data) { ___3493 set_size_in_words = ___3476->size / ___3479; ___3493 word; ___3480 word_val = 0; int bit; if (___3682 == ___333) { word = set_size_in_words - 1; bit = ___3479 - 1; if (word >= 0) { word_val = ___3476->data[word]; } } else if (___3682 > 0) { word = (___3682 - 1) / ___3479; bit = static_cast<int>((___3682 - 1) % ___3479); if (word >= 0) { word_val = ___3476->data[word] << (___3479 - bit - 1); } } else { return ___333; } while ((word >= 0) && (word_val == 0)) { word--; bit = static_cast<int>(___3479 - 1); if (word >= 0) { word_val = ___3476->data[word] << (___3479 - bit - 1); } } if (word >= 0) { while (!(word_val&___3498)) { word_val <<= 1; bit--; } next_member = word * ___3479 + bit; } } return next_member; } ___372 ___1175(___3501 ___3477, ___3501 ___3478) { ___3493 set1_size_in_words, set2_size_in_words, min_set_size_in_words, ___1841; if (!___3477 || !___3478) return ___1305; set1_size_in_words = ___3477->size / ___3479; set2_size_in_words = ___3478->size / ___3479; min_set_size_in_words = MIN(set1_size_in_words, set2_size_in_words); for (___1841 = 0; ___1841 < min_set_size_in_words; ___1841++) { { if (___3477->data[___1841] != ___3478->data[___1841]) return ___1305; } } for (___1841 = min_set_size_in_words; ___1841 < set1_size_in_words; ___1841++) { { if (___3477->data[___1841] != 0) return ___1305; } } for (___1841 = min_set_size_in_words; ___1841 < set2_size_in_words; ___1841++) { { if (___3478->data[___1841] != 0) return ___1305; } } return ___4226; } ___3501 intersection( ___3501 ___3477, ___3501 ___3478) { ___3501 ___3358 = ___29(___1305); ___3493 const largestMember = MAX(___1751(___3477),___1751(___3478)); if (___3358 && !___1201(___3358, largestMember, ___1305)) ___939(&___3358); if (___3358 && !___2015(___3477) && !___2015(___3478)) { ___3493 mOffset1 = ___1746(___3477); ___3493 mOffset2 = ___1746(___3478); for (; mOffset1 != ___333 && mOffset2 != ___333; ) { if (mOffset1 == mOffset2) (void)___17(___3358, mOffset1, ___1305); bool const advance1 = mOffset1 <= mOffset2; bool const advance2 = mOffset2 <= mOffset1; if (advance1) mOffset1 = ___1761(___3477, mOffset1); if (advance2) mOffset2 = ___1761(___3478, mOffset2); } } ENSURE(VALID_REF_OR_NULL(___3358)); return ___3358; } ___372 ___2062(___3501 ___486, ___3501 ___2973) { ___3493 s; ___1472(s, ___486) { if (!___1956(___2973, s)) return (___1305); } return (___4226); } ___3493 ___2404(___3501     ___3476, ___3493 ___2402) { ___3493 ___1832; ___3493 ___2866 = -1; if (___1956(___3476, ___2402)) { for (___1832 = 0; ___1832 <= ___2402; ___1832++) { if (___1956(___3476, ___1832)) ___2866++; } } return (___2866); } ___3493 ___2867(___3501     ___3476, ___3493 ___2866) { ___3493 ___1832; ___3493 ___2402 = ___333; for (___1832 = 0; ___1832 <= ___2866; ___1832++) { ___2402 = ___1761(___3476, ___2402); if (___2402 == ___333) break; } return (___2402); } ___372 ___677(___3501     ___1126, ___3493 ___1125, ___3501     ___3663, ___3493 ___3662) { if (___1956(___3663, ___3662)) return (___17(___1126, ___1125, ___4226)); else ___3334(___1126, ___1125); return (___4226); } void ___3560(___3501     ___3476, ___3493 ___3558, ___3493 ___3559, ___3493 ___3556) { ___3501     NewSet; ___3493 DPos; ___3493 SPos; if ((___3476 == NULL) || (___2015(___3476))) return; NewSet = ___29(___4226); if (NewSet == NULL) return; if (!___676(NewSet, ___3476, ___4226)) return; if (___3556 < 0) { DPos = ___3559; SPos = ___3558 - 1; while (DPos > ___3559 + ___3556) ___677(NewSet, DPos--, ___3476, SPos--); SPos = ___3559; while (SPos >= ___3558) ___677(NewSet, DPos--, ___3476, SPos--); } else if (___3556 > 0) { DPos       = ___3558; SPos       = ___3559 + 1; while (DPos < ___3558 + ___3556) ___677(NewSet, DPos++, ___3476, SPos++); SPos = ___3558; while (SPos <= ___3559) ___677(NewSet, DPos++, ___3476, SPos++); } ___676(___3476, NewSet, ___4226); ___939(&NewSet); } namespace {
 #if defined DEBUG_SET
void printWord(unsigned long word) { ___3480 ___2344 = 0x00000001; ___3480 shiftedw = word; for (int i = 0; i < ___3479; ++i) { if (___2344 & shiftedw) putchar('1'); else putchar('0'); shiftedw >>= 1; } } void printSet(___3501 ___3476) { ___3493 nWords = ___3476->size / ___3479; for (___3493 i = 0; i < nWords; ++i) { printWord(___3476->data[i]); putchar('|'); } putchar('\n'); }
 #endif 
void ShiftSetForDelete(___3501 ___3476, ___3493 DeletePos) { if ((___3476 == NULL) || (___2015(___3476))) return;
 #if defined DEBUG_SET
printf("Deleting member at %8ld in set: ",(long)DeletePos); printSet(___3476);
 #endif
___3493 nWords = ___3476->size / ___3479; ___3493 word_start_shift = DeletePos / ___3479; for (___3493 word = word_start_shift; word < nWords; ++word) { ___3480 word_val = ___3476->data[word]; ___3480 word_val_final = word_val; if (word > word_start_shift) { word_val_final >>= 1; } else { ___3480 mask1 = ((___3480)1 << DeletePos) - 1; ___3480 mask2 = ~mask1; ___3480 word_val_shifted = word_val; word_val_shifted >>= 1; word_val_shifted |= mask1; word_val |= mask2; word_val_final = (word_val & word_val_shifted); } if( word < nWords-1) { ___3480 word_val_next = ___3476->data[word+1]; ___3480 bit = (((___3480)1 & word_val_next) << (___3479-1)); word_val_final |= bit; } ___3476->data[word] = word_val_final; }
 #if defined DEBUG_SET
printf("Resulting set                     : "); printSet(___3476);
 #endif
} }