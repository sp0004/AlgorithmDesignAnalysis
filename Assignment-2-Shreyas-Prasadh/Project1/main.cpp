
// Assignment 2
// Author : Shreyas Prasadh
// Student Id : 0859565
// Date: 26th March 2018


#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector> 
#include <algorithm>
#include <functional>
#include <string>
#include "HashMap.h"
#include <unordered_map>
#include <regex>
#include <map>


using namespace std;

// Initializing a structure for HashMap
struct TwitterDB
{
	// Some fields are created keeping in mind the future requirements where all the data from the Doc will be used 
	string Tuser_id;
	string Tuser_name;
	string Tuser_txt;
	string Tuser_loc;
	int Tuser_retweetCount;
	bool Tuser_isRetweet;
	int Tuser_followC;
	string UserTweetName;
};
//Global Declaration
HashMap<string, TwitterDB> hashMap;

typedef HashMap<string, TwitterDB>::Iterator iterDeclaration;
vector<int> ArrayForCounting;
vector<string> TopFiveUserNames;

// Preprocessing and inserting data into hash Table
class PreprocessingData
{
	// This is a generic function which is used to remove all the special characters from word
	// eg :@CARadsCEO: will be CARadsCEO 
	// Note : The Preceding and forward characters are considered while manipulation of the strings
public:
	static string RemoveSpecials(string str)
	{
		int i = 0, len = str.length();
		while (i < len)
		{
			char c = str[i];
			if (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
			{
				if ((c >= 'A') && (c <= 'Z')) str[i] += 32; //Assuming dictionary contains small letters only.
				++i;
			}
			else
			{
				str.erase(i, 1);
				--len;
			}
		}
		return str;
	}
	// Reading the data from the csv and inserting into HashTable
public:
	static void PreproccessingAndInsertion()
	{
		try
		{
			ifstream inputfile("D:/study/RRR/Project1/Project1/docTweet.csv");
			if (!inputfile.is_open()) cout << "ERROR" << '\n';

			string TweetText;
			string Line;
			getline(inputfile, Line); //skipping the first line
			//Traverse line by line and reading the data
			while (getline(inputfile, Line))
			{
				std::istringstream StreamForReadingData{ Line }; // Creating a stream for reading of data
				vector<string> tokens; //Creating a vector to store the data 
				string token; //current token
				while (getline(StreamForReadingData, token, ','))
				{
					tokens.push_back(token); //add the token to the vector
				}

				//We are only concerned with the first two columns
				string UserID;
				string UserText;

				if (tokens.size() != 0)
				{
					UserText = tokens[1];
					UserID = tokens[0];

				}
				string word;
				stringstream WordsFromString(UserText);
				while (WordsFromString >> word)
				{
					std::size_t WordIndex = word.find('@');
					if (WordIndex == 0)
					{

						string UserTweetName = RemoveSpecials(word); // Remove all the special character
						TwitterDB access;   // initializing Hashmap
						access.Tuser_id = UserID;
						access.Tuser_txt = UserText;
						access.UserTweetName = UserTweetName;
						hashMap.Insert(UserID, access);  // inserting data into hashmap
						break;
					}
				}

			}
			inputfile.close();
		}
		catch (exception ex)
		{
			cout << "Exception Occured";
		}
	}
};

// HashMap processing and extracting top 5 processes	
class Top5User
{
	// This is to display all the User and Their name as the name suggest 
	// This function is commented for the purpose of clarity  
public:
	static void HashMapProccessing()
	{
		//Displaying all values 	
		cout << "\nALL USERS AND THEIR DATA : \n\n";
		for (int z = 0; z < hashMap.TableSize(); z++)
		{
			iterDeclaration iter = hashMap.begin(z);  // Declaring iteration 

			if (!hashMap.IsEmpty(z))
			{
				cout << "INDEX '" << hashMap.Hash(iter->value.Tuser_id) << "' DATA:\n";

				for (; iter != hashMap.end(z); ++iter)
				{
					cout << "\n\tUser ID: " << iter->value.Tuser_id
						<< "\n\tText: " << iter->value.Tuser_txt << endl
						<< "User Tweet Name" << iter->value.UserTweetName;

				}

			}
		}
	}

	//This is to display the Top5 Users and the most important one 
public:
	static void Top5Users()
	{
		try
		{
			vector<string> ArrayForTweetNameList;
			int searchWordSize = ArrayForTweetNameList.size();
			int count = 0;
			for (int z = 0; z < hashMap.TableSize(); ++z)
			{
				iterDeclaration iter = hashMap.begin(z);
				if (!hashMap.IsEmpty(z))
				{
					// The inner loop pushes the value from the hashMap
					for (; iter != hashMap.end(z); ++iter)  ArrayForTweetNameList.push_back(iter->value.UserTweetName);
				}

			}

			map<string, int> CountOfTweetName;
			// Iterating through Each Index for getting the count 
			for (const auto& EachIndex : ArrayForTweetNameList)
			{
				++CountOfTweetName[EachIndex];
			}
			// This sorts the Tweets in terms of the values (i.e the number of tweet names count)
			vector<pair<string, int>> top_five(5);
			partial_sort_copy(CountOfTweetName.begin(), CountOfTweetName.end(),
				top_five.begin(), top_five.end(),
				[](std::pair<const std::string, int> const& l, std::pair<const std::string, int> const& r)
			{
				return l.second > r.second;
			});
			cout << "The Top Tweet Users are shown below with their frequency" << endl;
			// Looping through for displaying the top 5 users
			for (const auto& EachTweet : top_five)
			{
				cout << EachTweet.first << " " << EachTweet.second << endl;
				TopFiveUserNames.push_back(EachTweet.first);
			}

		}
		catch (const std::exception&)
		{
			cout << "Exception Occured";
		}
	}
};
// The no of the columns in the DocTweet is 1000 . 
//The data structure chosen was Array . 
//The data is not as large, so Arrays has been chosen as a data store. They are easy to accesss and 
//manipulate also . They are also easier to implement than Linked List and other data structure in 
//addition to giving the same time complexity of O(n)
// I have made 5 different data sets for different users 
const int SizeOfArray = 1100;

string *ArrayOfTop1UserText = new string[SizeOfArray];
string *ArrayOfTop2UserText = new string[SizeOfArray];
string *ArrayOfTop3UserText = new string[SizeOfArray];
string *ArrayOfTop4UserText = new string[SizeOfArray];
string *ArrayOfTop5UserText = new string[SizeOfArray];
// Time complexity of Array : O(n)

// CRUD operations on the top users
class CRUDOperationOnTopUser {
	// generic function for storing text in array
private:
	static void TextStore(int p, string *ArrayName)
	{
		// The logic is similar to the how we extract data from the HashTable and display it the function
		// HashMapProccessing() with a few modifications 
		//Note : All the special characters are removed then the text considered
		// Eg : @CARadsCEO: and @CARadsCEO will be taken as @CARadsCEO
		
		PreprocessingData pre;
		for (int i = 0; i < hashMap.TableSize(); i++)
		{
			iterDeclaration iter = hashMap.begin(i);
			if (!hashMap.IsEmpty(i)) {
				for (; iter != hashMap.end(i); ++iter)
				{
					// The Cout line is comment for better readability during output phase . The function of it is just to print
					//the userName and UserTweet
					if (TopFiveUserNames[p] == pre.RemoveSpecials(iter->value.UserTweetName))
						//cout << "\n\tText:" << iter->value.Tuser_txt << endl
						//<< "User Tweet Name" << iter->value.UserTweetName;
					ArrayName[i] = iter->value.Tuser_txt;
				}
			}
		}

	}

// We now have to insert Text from the tweets in Array , This function does that
public:
	static void InsertUserTexts() {

		cout << "Insertion of tweets in progress .. Please wait till press any continue comes" << endl;
		for (int p = 0; p < TopFiveUserNames.max_size(); p++)
		{
			if (p == 0)
			{
				TextStore(0, ArrayOfTop1UserText);
			}
			else if (p == 1)
			{
				TextStore(1, ArrayOfTop2UserText);
			}
			else if (p == 2)
			{
				TextStore(2, ArrayOfTop3UserText);
			}
			else if (p == 3)
			{
				TextStore(3, ArrayOfTop4UserText);
			}
			else if (p == 4)
			{
				TextStore(4, ArrayOfTop5UserText);
			}

		}

	}
};


int main()
{
	PreprocessingData pre;
	pre.PreproccessingAndInsertion();
	Top5User top;
	//top.HashMapProccessing();
	top.Top5Users();
	CRUDOperationOnTopUser Operation;
	Operation.InsertUserTexts();
	system("pause");

}


