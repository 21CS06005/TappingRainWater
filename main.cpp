#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Calculating maximum height of elevation from each elevation
// Check for elevations towards right if flag = 1
// Check for elevations towards left if flag = 0
vector<int> calculating_max(vector<int> heights, int num_elevations, int flag) {
  vector<int> max_height;
  int max_elevation = 0;

  if(flag == 1) {
    // Perform the calculation by checking the elevations towards the right side of the current elevation
    for(int i=0; i<num_elevations; i++) {
      if(heights[i] > max_elevation) {
        max_height.push_back(0);
        max_elevation = heights[i];
      }
      else {
        max_height.push_back(max_elevation);
      }
    }
  }
  else {
    // Perform the calculation by checking the elevations towards the left side of the current elevation
    max_elevation = 0;
    for(int i=num_elevations - 1; i>=0; i--) {
      if(heights[i] > max_elevation) {
        max_height.push_back(0);
        max_elevation = heights[i];
      }
      else {
        max_height.push_back(max_elevation);
      }
    }
    reverse(max_height.begin(), max_height.end());
  }

  return max_height;
}

// Function to calculate the amount of rain water tapped
int calculate_amt_tapped_water(vector<int> heights, vector<int> max_height_left, vector<int> max_height_right, int num_elevations) {
  vector<int> difference;
  int min = 0, sum=0;
  for(int i=0; i<num_elevations; i++) {
    min = max_height_left[i];
    if(max_height_right[i] < min)
      min = max_height_right[i];
    
    if(heights[i] < min)
      difference.push_back(min - heights[i]);
    else
      difference.push_back(0);
  }
  for(int i=0; i<num_elevations; i++) {
    sum += difference[i];
  }
  
  return sum;
}

// Function to count the number of distinct key subsequences in the given string
int counting_distinct_subseq(string str, string key) {
  char dp_array[key.length() + 1][str.length() + 1];
  
  // Initializing the array with zero, to hadnle the grabage values
  for(int i=0; i<=key.length();i++) {
    for(int j=0; j<=str.length(); j++) {
      if(i == 0)
        dp_array[i][j] = 1;
      else
        dp_array[i][j] = 0;
    } 
  }

  for(int i=1; i<=key.length();i++) {
    for(int j=1; j<=str.length(); j++) {
      if(key[i-1]==str[j-1])
      {
        dp_array[i][j]=dp_array[i-1][j-1]+dp_array[i][j-1];
      }
      else
        dp_array[i][j]=dp_array[i][j-1];
    }
  }
  return dp_array[key.length()][str.length()]; 
}

int main() {
  // First question - caluculating the amount of rain water tapped
  cout<<"-------------First Question - Tapping rain water--------------"<<endl<<endl;

  int num_elevations, temp;
  
  cout<<"Enter the number of elevations:"<<endl;
  cin>>num_elevations;
  vector<int> heights, max_height_left, max_height_right;

  cout<<"Enter the heights of the elevations:"<<endl;
  for(int i=0; i<num_elevations; i++) {
    cin>>temp;
    heights.push_back(temp);
  }

  max_height_left = calculating_max(heights, num_elevations, 1);
  max_height_right = calculating_max(heights, num_elevations, 2);
  
  int result = calculate_amt_tapped_water(heights, max_height_left, max_height_right, num_elevations);

  cout<<"Amount of water tapped = "<<result<<endl;

  // Second question - caluculating the number of distinct key subsequences in the given string
  cout<<endl<<endl<<"------Second Question - number of distinct subsequences------"<<endl<<endl;

  string str, key;
  cout<<"Enter the string to be checked in:"<<endl;
  cin>>str;
  cout<<"Enter the key:"<<endl;
  cin>>key;

  // Converting the string and key to lower case
  transform(str.begin(), str.end(), str.begin(), ::tolower);
  transform(key.begin(), key.end(), key.begin(), ::tolower);

  cout<<endl;
  cout<<"String in lower case is: "<<str<<endl;
  cout<<"Key in lower case is: "<<key<<endl;

  int count = counting_distinct_subseq(str,key);
  cout<<endl<<"Count of distinct subsequences = "<<count<<endl;
} 