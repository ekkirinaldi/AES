#include<bits/stdc++.h>
using namespace std;

int plain[4][4];
string h;
int cipher[4][4];
struct rk{
	int key[4][4]; 
};

rk roundkey[11];

unsigned char rcon[][4] =
{
	{
		0x01, 0x00, 0x00, 0x00
	},
	{
		0x02, 0x00, 0x00, 0x00
	},
	{
		0x04, 0x00, 0x00, 0x00
	},
	{
		0x08, 0x00, 0x00, 0x00
	},
	{
		0x10, 0x00, 0x00, 0x00
	},
	{
		0x20, 0x00, 0x00, 0x00
	},
	{
		0x40, 0x00, 0x00, 0x00
	},
	{
		0x80, 0x00, 0x00, 0x00
	},
	{
		0x1B, 0x00, 0x00, 0x00
	},
	{
		0x36, 0x00, 0x00, 0x00
	},
	{
		0x6C, 0x00, 0x00, 0x00
	},
	{
		0xD8, 0x00, 0x00, 0x00
	},
	{
		0xAB, 0x00, 0x00, 0x00
	},
	{
		0x4D, 0x00, 0x00, 0x00
	},
	{
		0x9A, 0x00, 0x00, 0x00
	}
};

int mat[][4] = 
{
	{
		2,3,1,1
	},
	{
		1,2,3,1
	},
	{
		1,1,2,3
	},
	{
		3,1,1,2
	}
};

unsigned char sbox[256] = 
 {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
 };


void transform(int a[][4]){
	int temp[4][4];
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			temp[j][i] = a[i][j];
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			a[i][j] = temp[i][j];
		}
	}
}

void sboks2Dimensi(int a[][4]){
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cipher[i][j] = sbox[cipher[i][j]];
		}
	}
}

int gmul(int a, int b) {
	int p = 0; /* the product of the multiplication */
	while (b) {
            if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
                p ^= a; /* since we're in GF(2^m), addition is an XOR */

            if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
                a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) -- you can change it but it must be irreducible */
            else
                a <<= 1; /* equivalent to a*2 */
            b >>= 1;
	}
	return p;
}

void konvertAsciiDes(string s, int mode){
	int k,l;
	k=0;
	
	l = s.length();
	for(int i=l;i<16;i++){
		s[i] = '\0';
	}
	if(mode == 0){
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				plain[i][j] = s[k];
				k++;
			}
		}
	}else{
		for(int i=0;i<4;i++){
			for(int j=0;j<4;j++){
				roundkey[0].key[i][j] = s[k];
				k++;
			}
		}
	}
}

void konvertDesHex(int a){
	char temp[2];
	
	itoa(a,temp,16);
	h = h + temp[0] + temp[1] + " ";
}

void geser(int a[],int g){
	int temp[4];
	for(int i=0;i<4;i++){
		temp[i]=((i+g) > 3 ? a[(i+g)-4] : a[i+g]);
	}
	for(int i=0;i<4;i++){
		a[i] = temp[i];
	}
}

void buatRoundKey(){
	int shf[4];
	for(int i=0;i<10;i++){
		for(int j=0;j<4;j++){
			shf[j]=((j+1) > 3 ? roundkey[i].key[3][0] : roundkey[i].key[3][j+1]);
		}

		for(int j=0;j<4;j++){
			shf[j] = sbox[shf[j]];
		}

		for(int j=0;j<4;j++){
			shf[j] ^= rcon[i][j];
		}

		for(int j=0;j<4;j++){
			roundkey[i+1].key[0][j] = roundkey[i].key[0][j] ^ shf[j];
		}

		for(int j=0;j<4;j++){
			roundkey[i+1].key[1][j] = roundkey[i+1].key[0][j] ^ roundkey[i].key[1][j];
		}

		for(int j=0;j<4;j++){
			roundkey[i+1].key[2][j] = roundkey[i+1].key[1][j] ^ roundkey[i].key[2][j];
		}

		for(int j=0;j<4;j++){
			roundkey[i+1].key[3][j] = roundkey[i+1].key[2][j] ^ roundkey[i].key[3][j];
		}	
	}
}

void addRoundKey(int a[][4], int b[][4]){
	int temp[4][4];
	for(int i = 0;i<4;i++){
		for(int j=0;j<4;j++){
			temp[i][j] = a[i][j] ^ b[i][j];
		}
	}
	for(int i = 0;i<4;i++){
		for(int j=0;j<4;j++){
			cipher[i][j] = temp[i][j];
		}
	}
}

void kalimatriks(int a[][4], int b[][4]){
	int temp[4][4];
	
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			temp[i][j] = gmul(a[i][0],b[0][j]) ^ gmul(a[i][1],b[1][j]) ^ gmul(a[i][2],b[2][j]) ^ gmul(a[i][3],b[3][j]);
			
		}
	}
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			cipher[i][j] = temp[i][j];
		}
	}
}


main(){
	string s;
	int l,k;
	cout << "Masukkan plaintext (max 16 karakter)" << endl;
	getline(cin, s);
	konvertAsciiDes(s,0);
	s="";
	
	cout << "Masukkan key (max 16 karakter)" << endl;
	getline(cin, s);
	konvertAsciiDes(s,1);
	s="";
	
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			konvertDesHex(plain[i][j]);
		}
	}
	cout << "Plaintext ke Hex :" << endl;
	cout << h << endl;
	cout << endl;
	h = "";
	
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			konvertDesHex(roundkey[0].key[i][j]);
		}
	}
	cout << "Key ke Hex :" << endl;
	cout << h << endl;
	cout << endl;
	h = "";
	
	buatRoundKey();
	
	transform(plain);
	transform(roundkey[0].key);
	cout << "Add Round Key pada putaran ke 0"<< endl;
	addRoundKey(plain, roundkey[0].key);
	transform(cipher);
	for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				konvertDesHex(cipher[j][k]);
			}
		}
	cout << h << endl;
	cout << endl;
	h = "";
	transform(cipher);
	
	for(int i=1;i<=10;i++){
		cout << "Subtitution Box pada putaran ke "<< i << endl;
		sboks2Dimensi(cipher);
		transform(cipher);
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				konvertDesHex(cipher[j][k]);
			}
		}
		cout << h << endl;
		cout << endl;
		h = "";
		transform(cipher);
		
		cout << "Shift pada putaran ke "<< i << endl;
		geser(cipher[0],0);
		geser(cipher[1],1);
		geser(cipher[2],2);
		geser(cipher[3],3);
		transform(cipher);
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				konvertDesHex(cipher[j][k]);
			}
		}
		cout << h << endl;
		cout << endl;
		h = "";
		transform(cipher);
		
		if(i==10){
		}else{
			cout << "Mix Column pada putaran ke "<< i << endl;
			kalimatriks(mat,cipher);
			transform(cipher);
			for(int j=0;j<4;j++){
				for(int k=0;k<4;k++){
					konvertDesHex(cipher[j][k]);
				}
			}
			cout << h << endl;
			cout << endl;
			h = "";
			transform(cipher);
		}
		
		cout << "Round key ke " << i << endl;
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				konvertDesHex(roundkey[i].key[j][k]);
			}
		}
		cout << h << endl;
		cout << endl;
		h = "";
		transform(roundkey[i].key);
		
		cout << "Add Round key pada putaran ke " << i << endl;
		addRoundKey(cipher, roundkey[i].key);
		transform(cipher);
		for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				konvertDesHex(cipher[j][k]);
			}
		}
		cout << h << endl;
		cout << endl;
		h = "";
		transform(cipher);
	}
	
	cout << "Maka cipher teksnya adalah" << endl;
	int i=0;
	for(int j=0;j<4;j++){
			for(int k=0;k<4;k++){
				s[i] = cipher[j][k];
				i++;
			}
	}
	for(int i=0;i<16;i++){
		cout << s[i];
	
	}
	cout << endl;

}