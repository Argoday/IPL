
#include "CryptChar.h"

namespace Crypt {

void CryptChar::setValue(const CharType & _char){
	int temp=_char;
	switch (temp){
		case 32:value = -1;break;
		case 63:value = -2;break;

		case 65:value =  0;break;case 66:value =  1;break;case 67:value =  2;break;case 68:value =  3;break;case 69:value =  4;break;
		case 70:value =  5;break;case 71:value =  6;break;case 72:value =  7;break;case 73:value =  8;break;case 74:value =  9;break;
		case 75:value = 10;break;case 76:value = 11;break;case 77:value = 12;break;case 78:value = 13;break;case 79:value = 14;break;
		case 80:value = 15;break;case 81:value = 16;break;case 82:value = 17;break;case 83:value = 18;break;case 84:value = 19;break;
		case 85:value = 20;break;case 86:value = 21;break;case 87:value = 22;break;case 88:value = 23;break;case 89:value = 24;break;
		case 90:value = 25;break;

		case  97:value =  0;break;case  98:value =  1;break;case  99:value =  2;break;case 100:value =  3;break;case 101:value =  4;break;
		case 102:value =  5;break;case 103:value =  6;break;case 104:value =  7;break;case 105:value =  8;break;case 106:value =  9;break;
		case 107:value = 10;break;case 108:value = 11;break;case 109:value = 12;break;case 110:value = 13;break;case 111:value = 14;break;
		case 112:value = 15;break;case 113:value = 16;break;case 114:value = 17;break;case 115:value = 18;break;case 116:value = 19;break;
		case 117:value = 20;break;case 118:value = 21;break;case 119:value = 22;break;case 120:value = 23;break;case 121:value = 24;break;
		case 122:value = 25;break;

		default:value = 0;
	}
}

CryptChar::operator CharType() const {
	switch (value){
		case -2:return '?';
		case -1:return ' ';

		case  0:return 'A';case  1:return 'B';case  2:return 'C';case  3:return 'D';case  4:return 'E';case  5:return 'F';case  6:return 'G';case  7:return 'H';case  8:return 'I';case  9:return 'J';
		case 10:return 'K';case 11:return 'L';case 12:return 'M';case 13:return 'N';case 14:return 'O';case 15:return 'P';case 16:return 'Q';case 17:return 'R';case 18:return 'S';case 19:return 'T';
		case 20:return 'U';case 21:return 'V';case 22:return 'W';case 23:return 'X';case 24:return 'Y';case 25:return 'Z';
		default:return 'z';
	}
	return 'z';
}
CryptChar::operator NumberType() const {
	return value;
}

}