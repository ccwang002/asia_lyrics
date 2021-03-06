#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

typedef struct ZY_struct {
	int count;
	char ZY[4];
} ZY_Struct;

void last_word_ZY( fstream &, fstream &, ZY_Struct * );
void search_ZY( int *, char *, char **, char *** );
void set_ZY_table( char ** );

int main( int argc, char *argv[] )
{
	fstream tin, fin, fou;
	tin.open( argv[1], ios::in ); // lyrics file
	fin.open( argv[2], ios::in ); // dictionary
	fou.open( argv[3], ios::out | ios::app );
	
	int year;
	tin >> year;
	
	ZY_Struct *result = new ZY_Struct[5];
	last_word_ZY( fin, tin, result );
	
	fou << year << " ";
	for (int i=0; i<5; i++)
	    fou << result[i].ZY << " " << result[i].count << " ";
	fou << endl;
	
	tin.close();
	fin.close();
	fou.close();
	
	return 0;
}

void last_word_ZY( fstream &fin, fstream &tin, ZY_Struct *result )
{
	char *pch;
	char *line = new char[200];
	char *lastword = new char[3];
	
	char ***dictionary = new char**[13032];
	for( int i=0; i<13032; i++ ) {
		dictionary[i] = new char*[2];
		dictionary[i][0] = new char[3];
		dictionary[i][1] = new char[3];
	}
	
	for( int i=0; i<13032; i++ ) {
		fin.getline( line, 99 );
		pch = strtok( line, " " );
		strncpy( dictionary[i][0], pch, 3 );
		pch = strtok( NULL, " " );
		strncpy( dictionary[i][1], pch, 3 );
	}
	
	int *ZY_count = new int[37];
	char **ZY_table = new char*[37];
	for( int i=0; i<37; i++ ) {
		ZY_count[i] = 0;
		ZY_table[i] = new char[3];
	}
	
	set_ZY_table( ZY_table );
	
	while( tin.getline( line, 199 ) != NULL ) {
		pch = strtok( line, " " );
		while( pch != NULL ) {
			
			if( int(pch[strlen(pch)-1]) == 13 ) {
				lastword[0] = pch[strlen(pch)-4];
				lastword[1] = pch[strlen(pch)-3];
				lastword[2] = pch[strlen(pch)-2];
			}
			else {
				lastword[0] = pch[strlen(pch)-3];
				lastword[1] = pch[strlen(pch)-2];
				lastword[2] = pch[strlen(pch)-1];
			}
			
			search_ZY( ZY_count, lastword, ZY_table, dictionary );
			pch = strtok( NULL, " " );
		}
	}
	
	multimap <int, int> map;
	multimap <int, int>::iterator it;
	for( int i=0; i<37; i++ )
		map.insert( pair<int, int>( ZY_count[i], i ) );
	
	it = map.end();
	for( int i=0; i<5; i++ ) {
		it--;
		result[i].count = int((*it).first);
		strncpy( result[i].ZY, ZY_table[(*it).second], 3 );
		result[i].ZY[3] = '\0';
	}
	
	for( int i=0; i<13032; i++ ) {
		for( int j=0; j<2; j++ ) {
			delete [] dictionary[i][j];
		}
	}
	for( int i=0; i<37; i++ )
		delete [] ZY_table[i];
	
	delete [] dictionary;
	delete [] ZY_table;
	delete [] ZY_count;
	delete [] lastword;
	delete [] line;
}

void search_ZY( int *ZY_count, char *lastword, char **ZY_table, char ***dictionary )
{
	for( int i=0; i<13032; i++ ) {
		if( strcmp( lastword, dictionary[i][0] ) == 0 ) {
			for( int j=0; j<37; j++ ) {
				if( strcmp( dictionary[i][1], ZY_table[j] ) == 0 ) {
					ZY_count[j]++;
					break;
				}
			}
			break;
		}
	}
}

void set_ZY_table( char **ZY )
{
	string temp;
	
	temp = "ㄅ"; strncpy( ZY[0],  temp.c_str(), 3 );
	temp = "ㄆ"; strncpy( ZY[1],  temp.c_str(), 3 );
	temp = "ㄇ"; strncpy( ZY[2],  temp.c_str(), 3 );
	temp = "ㄈ"; strncpy( ZY[3],  temp.c_str(), 3 );
	temp = "ㄉ"; strncpy( ZY[4],  temp.c_str(), 3 );
	temp = "ㄊ"; strncpy( ZY[5],  temp.c_str(), 3 );
	temp = "ㄋ"; strncpy( ZY[6],  temp.c_str(), 3 );
	temp = "ㄌ"; strncpy( ZY[7],  temp.c_str(), 3 );
	temp = "ㄍ"; strncpy( ZY[8],  temp.c_str(), 3 );
	temp = "ㄎ"; strncpy( ZY[9],  temp.c_str(), 3 );
	temp = "ㄏ"; strncpy( ZY[10], temp.c_str(), 3 );
	temp = "ㄐ"; strncpy( ZY[11], temp.c_str(), 3 );
	temp = "ㄑ"; strncpy( ZY[12], temp.c_str(), 3 );
	temp = "ㄒ"; strncpy( ZY[13], temp.c_str(), 3 );
	temp = "ㄓ"; strncpy( ZY[14], temp.c_str(), 3 );
	temp = "ㄔ"; strncpy( ZY[15], temp.c_str(), 3 );
	temp = "ㄕ"; strncpy( ZY[16], temp.c_str(), 3 );
	temp = "ㄖ"; strncpy( ZY[17], temp.c_str(), 3 );
	temp = "ㄗ"; strncpy( ZY[18], temp.c_str(), 3 );
	temp = "ㄘ"; strncpy( ZY[19], temp.c_str(), 3 );
	temp = "ㄙ"; strncpy( ZY[20], temp.c_str(), 3 );
	temp = "ㄚ"; strncpy( ZY[21], temp.c_str(), 3 );
	temp = "ㄛ"; strncpy( ZY[22], temp.c_str(), 3 );
	temp = "ㄜ"; strncpy( ZY[23], temp.c_str(), 3 );
	temp = "ㄝ"; strncpy( ZY[24], temp.c_str(), 3 );
	temp = "ㄞ"; strncpy( ZY[25], temp.c_str(), 3 );
	temp = "ㄟ"; strncpy( ZY[26], temp.c_str(), 3 );
	temp = "ㄠ"; strncpy( ZY[27], temp.c_str(), 3 );
	temp = "ㄡ"; strncpy( ZY[28], temp.c_str(), 3 );
	temp = "ㄢ"; strncpy( ZY[29], temp.c_str(), 3 );
	temp = "ㄣ"; strncpy( ZY[30], temp.c_str(), 3 );
	temp = "ㄤ"; strncpy( ZY[31], temp.c_str(), 3 );
	temp = "ㄥ"; strncpy( ZY[32], temp.c_str(), 3 );
	temp = "ㄦ"; strncpy( ZY[33], temp.c_str(), 3 );
	temp = "ㄧ"; strncpy( ZY[34], temp.c_str(), 3 );
	temp = "ㄨ"; strncpy( ZY[35], temp.c_str(), 3 );
	temp = "ㄩ"; strncpy( ZY[36], temp.c_str(), 3 );
}

// int main( int argc, char *argv[] )
// {
	// FILE *fin  = fopen( argv[1], "r" );
    // FILE *fout = fopen( argv[2], "w" );
	
	// int ***year = new int**[60];
	// for( int i=0; i<60; i++ ) {
		// year[i]  = new int*[37];
		// for( int j=0; j<37; j++ ) {
			// year[i][j] = new int[1];
			// year[i][j][0] = 0;
		// }
	// }
	
	// char **ZY = new char*[37];
	// for( int i=0; i<37; i++ )
		// ZY[i] = new char[3];
	
	// set_ZY_table( ZY );
	
	// int year_data, times;
	// char *ZY_data = new char[3];
	// char *line = new char[50];
	
	// for( int i=0; i<185303; i++ ) {
		// fscanf( fin, "%d", &year_data );
		// if( year_data >= 1956 && year_data <= 2015 ) {
			// fscanf( fin, "%s", &ZY_data[0] );
			// fscanf( fin, "%d", &times );
			// if( times != 0 ) {
				// for( int j=0; j<37; j++ ) {
					// if( strcmp( ZY_data, ZY[j] ) == 0 )
						// year[year_data-1956][j][0] += 1;
				// }
			// }
			// fscanf( fin, "%s", &ZY_data[0] );
			// fscanf( fin, "%d", &times );
			// if( times != 0 ) {
				// for( int j=0; j<37; j++ ) {
					// if( strcmp( ZY_data, ZY[j] ) == 0 )
						// year[year_data-1956][j][0] += 1;
				// }
			// }
		// }
		// fgets( line, 49, fin );
	// }
	
	// int max;
	
	// for( int i=0; i<60; i++ ) {
		// max = 0;
		// for( int j=0; j<37; j++ ) {
			// if( year[i][j][0] > max )
				// max = year[i][j][0];
		// }
		// fprintf( fout, "%d   ", i+1956 );
		// if( max == 0 )
			// fprintf( fout, "-- " );
		// else {
			// for( int j=0; j<37; j++ ) {
				// if( year[i][j][0] == max ) {
					// fprintf( fout, "%s %d ", ZY[j], max );
				// }
			// }
		// }
		// fprintf( fout, "\n" );
	// }
	
	// for( int i=0; i<60; i++ ) {
		// for( int j=0; j<37; j++ )
			// delete [] year[i][j];
		// delete [] year[i];
	// }
	// delete [] year;
	
	// for( int i=0; i<37; i++ )
		// delete [] ZY[i];
	// delete [] ZY;
	
	// delete [] ZY_data;
	// delete [] line;
	
	// fclose( fin );
	// fclose( fout );
	
	// return 0;
// }