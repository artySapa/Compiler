# Compiler

https://user-images.githubusercontent.com/118086930/235388605-5dddb4aa-6f81-4764-bb16-b1cab0c18984.mov

## Description
Given a simple algorithm for the processing arbitrary number of lines of code, including noticing scopes, I made a better algorithm to reduce the time spent on processing. The Final performance for 400000 lines of code reduced from ~2500 msec to ~11 msec. To use it, fisr uncomment the generateTests file and run only this file. Then comment it out again and use the testNameTable file to go through the algorithms.

## Data structures used
My NameTableImpl has 3 private members: vector of vectors of strings to take track of scopes and variables that were introduced in that particular scope, the latest integer that takes track of the last scope that we entered, and hash table hash.
	
My hash table is a separate class called HashTable and contains 2 private members: struct Bucket that contains a string, line it was declared and a scope it was declared in, and an array of lists of Buckets buckets[19998] to keep variables that were declared in a particular scope and at a particular line.

When entering a scope, a new vector is pushed to the scopes vector and when exiting a scope, the last vector is popped from the scopes vector.
When declaring a function, my program adds it to a hash table, taking into account the line and scope it was declared. When exiting a scope, all the variables with the scope are removed from the hash table.

Time complexities for the functions
enterScope() – constant time
exitScope() – O(N) where N is the number of elements declared in a scope
declare(const string& id, const int& lineNum) – O(1) if the new scope or a variable was not declared before, O(N) where N is the number of times a variable was declared if it was declared before(or the id of hashFunc is the same for some other variable, but I check for that too)
find(const string& id) – O(N) or O(1) for the same reason as for the declare function. 

## Algorithms used

### HashTable:

bool insert(const string& s, const int& lineNum, const int& scope)

	Find an index using the hash function
	If the bucket at the index is not empty
		Iterate through each element in the bucket
			If the name is the same as s and the scope is the same as the scope value
				Return false
	Create a new bucket with all the data
	Push front the new bucket to the bucket’s list at the index
	Return True

int find(const string& s) const

	Find an index using the hash function
	If the bucket at the index is empty
		Return -1
	Iterate through each element in the bucket
		Return line if the variable is found(the earliest one as we were pushing front declaring)
	Return -1

bool remove(const string& s)

	Find an index using the hash function
	If the bucket at the index is empty
		Return false
	Pop the first element at the bucket
	Return true;

int hashFunc(const string& s) const

	Generate the index using the std hash function and dividing it by 19997
	Return the number


### NameTableImpl:

bool NameTableImpl::exitScope()

	If the size of scopes is 1
		Return false
	For each element in the scope
		Remove the value from the hash table
	Decrease the latest value
	Pop back the scopes vector
	Return true

bool NameTableImpl::declare(const string& id, const int& lineNum)

	If the scopes vector is empty
		Create a vector and push it back to scopes
	If hash’s insert for the latest scope returns false
		Return false
	Push back the variable to the latest scope
	Return true;

