#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;

class Table
{
	private:
		int Length;
		int WinCondition;
		vector<string> Row;
		vector<string> Column;
		int R, B;
		
		void CheckNChar( string s )
		{
/*
			int tempR, tempB;

			tempR = count( s.begin(), s.end(), 'R' );
			tempB = count( s.begin(), s.end(), 'B' );
			cout << "s: " << s << endl;
			cout << "R: " << tempR << " ,";
			cout << "B: " << tempB << endl;

			if( tempR == this->WinCondition )
				R=1;
			if( tempB == this->WinCondition )
				B=1;
		
*/
			char flag;
			int Rcount, Bcount;

			flag = s[0];
			Rcount = 1;
			Bcount = 1;

			for( unsigned int i=1; i<s.length(); i++ )
			{
				if( s[i] == flag )
				{
					if( s[i] == 'R' )
						Rcount++;
					if( s[i] == 'B' )
						Bcount++;
					if( Rcount == this->WinCondition )
						this->R = 1;
					if( Bcount == this->WinCondition )
						this->B = 1;
				}
				else
				{
					Rcount = 1;
					Bcount = 1;
				}

				flag = s[i];
			}
		}
		void CheckWhoWin( void )
		{
			string temp;
			string temp2;
			string temp3;
			string temp4;
			// check rows
			for( int i=0; i<this->Length; i++ )
			{
				this->CheckNChar( this->Row[i] );
				for( int j=0; j<this->Length; j++ )
				{
					temp += Row[j][i];
				//	cout << "59: " << temp << endl;
				}
				this->CheckNChar( temp );
				temp.clear();
				
				for( int j=0; j<this->Length - i; j++ )
				{
					temp += Row[j][i+j];
					temp2 += Row[i+j][j];
					temp3 += Row[j][this->Length - 1 - i - j];
					temp4 += Row[i+j][this->Length - 1 - j];
				}
				this->CheckNChar( temp );
				this->CheckNChar( temp2 );
				this->CheckNChar( temp3 );
				this->CheckNChar( temp4 );
				temp.clear();
				temp2.clear();
				temp3.clear();
				temp4.clear();
			}
			
		}
		void Gravity( void )
		{
			string empty, Nempty;
			string temp;

			for( int i=0; i<this->Length; i++ )
			{
				temp = this->Column[i];
				for( int j=0; j<this->Length; j++ )
				{
					if( temp[j] == '.' )
					{
						empty += temp[j];
					}
					else
					{
						Nempty += temp[j];
					}
				}
				temp = empty + Nempty;
				this->Column[i] = temp;
				temp.clear();
				empty.clear();
				Nempty.clear();
			}
		}
		void Rotate( void )
		{
			string temp;
			this->Column.clear();

			for( int i=0; i<this->Length; i++ )
			{
				temp = Row.back();
				Column.push_back( temp );
				Row.pop_back();
			}
		}
		void ColtoRow( void )
		{
			this->Row.clear();

			string temp;
			for( int i=0; i<this->Length; i++ )
			{
				for( int j=0; j<this->Length; j++ )
				{
					temp += this->Column[j].front();
					this->Column[j].erase( this->Column[j].begin() );
				}
				this->Row.push_back( temp );
				temp.clear();
			}
		}
	public:
		void InputWinCondition( int K )
		{
			this->WinCondition = K;
			this->R = 0;
			this->B = 0;
		}
		void Play( void )
		{
			this->Rotate();
			this->Gravity();
			this->ColtoRow();
			this->CheckWhoWin();
		}
		void InputTableLen( int l )
		{
			this->Length = l;
		}
		void InputTableRow( string r )
		{
			this->Row.push_back(r);
		}
		string OutputTable( void )
		{
			string output;

			for( int i=0; i<this->Length; i++ )
			{
				output.append(Row[i]);
				output.append("\n");
			}

			return output;
		}
		string WhoWin( void )
		{
			if( R > 0 && B > 0 )
				return "Both";
			if( R == 0 && B == 0 )
				return "Neither";
			if( R > 0 && B == 0 )
				return "Red";
			if( R == 0 && B > 0 )
				return "Blue";
			return "";
		}
};

int main( int argv, char** argc )
{
	int T, N, K;
	ifstream myfile;
	myfile.open( argc[1] );
	string rowtemp;

	myfile >> T;
	//cout << T << endl;

	for( int i=0; i<T; i++ )
	{
		myfile >> N >> K;
		//cout << N << " ," << K << endl;
		
		Table table;
		table.InputTableLen( N );
		table.InputWinCondition( K );
		for( int j=0; j<N; j++ )
		{
			myfile >> rowtemp;
			table.InputTableRow( rowtemp );
		}

		table.Play();
		//cout << table.OutputTable() << endl;
		cout << "Case #" << i+1 << ": " << table.WhoWin() << endl;
	}
	
	myfile.close();
	return 0;
}

