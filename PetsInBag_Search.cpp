//Bryant Wong
//CSCI2312 Final Project

//Implementation File for PetsInBag_Search.cpp
//Header file is in PetsInBag_Search.h

#include <iostream>
#include <string>
#include "PetsInBag_Search.h"
#include <algorithm>
#include <memory>
#include <fstream>


namespace csci2312

{
	// Default constructor
	Pet_T::Pet_T() { };

	// Contructor to sets name and tag
	Pet_T::Pet_T(string p_name, string p_tag, string p_illness) 
	{
		//  tag is a unique Pet identifier 
		tag = p_tag;
		name = p_name;		
		illness = p_illness;
	};	
		
	// Destructor
	Pet_T::~Pet_T() {};
	
	void Pet_T::setName(string p_name) 
	{
		name = p_name;
	}
		
	string Pet_T::getName() const 
	{
		return name;
	}
		
	void Pet_T::setTag(string p_tag) 
	{
		tag = p_tag;
	}
	string Pet_T::getTag() const 
	{
		return tag;
	}
	void Pet_T::setIllness(std::string p_illness)
	{
		illness = p_illness;
	}
	std::string Pet_T::getIllness() const
	{
		return illness;
	}

	void Pet_T::whoAmI() const {};
	//void Pet_T::healAndSpeak() const {};

	//some error checking
	// to check is integer from stack overflow, modified to accept my parameters
	//http://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int
	inline bool isInteger(const std::string& string)
	{
		if (string.empty() || ((!isdigit(string[0])) && (string[0] != '-') && (string[0] != '+')))
			return false;
		char *charPtr;
		strtol(string.c_str(), &charPtr, 10);
		return(*charPtr == 0);
	}


	

	istream& operator >>(istream& ins, Pet_T& the_object)
		//Overloads the >> operator for input values of type Pet_T.
		//Precondition: If ins is a file input stream, then ins has already been
		//connected to a file.
	{		 
		std::cout << "Enter pet name" << std::endl;
		std::getline(ins >>std::ws,the_object.name);
		std::cout << "Enter the pet's 3-digit ID tag" << std::endl;
		std::getline(ins >> std::ws, the_object.tag);
		while (the_object.tag.size() != 3 || !isInteger(the_object.tag))
		{
			std::cout << "Invalid entry, please enter a valid 3-digit ID tag" << std::endl;
			std::getline(ins >> std::ws, the_object.tag);
		}
		std::cout << "Enter pet illness" << std::endl;
		std::getline(ins >> std::ws, the_object.illness);
		return ins;		
	};

	ostream& operator <<(ostream& outs, const Pet_T& the_object)
	//Overloads the << operator for output values of type Pet_T.
	//Precondition: If outs is a file output stream, then outs has already been
	//connected to a file.
	{		
		the_object.whoAmI();
		outs << endl;
	    return outs;		
	}

	// A sort predicate as a member function, same logic as in non-member
	bool Bag_T::sortPetPredicate_member(PetPtr p1, PetPtr p2) 
	{
		return(p1->getTag() < p2->getTag());
	}
		
	// Needed for STL "sort" algorithm
	bool sortPetPredicate(PetPtr p1, PetPtr p2) {
		return(p1->getTag() < p2->getTag());
	}

	// Needed for STL "search" algorithm
	//DONE
	//changed to shared_ptr smart pointer version
	bool searchPetPredicate(PetPtr p1, PetPtr p2) 
	{
		// to be finished, if the search generic algorithm is used
		//modified, added functionality for "search" generic algorithm
		if (p1->getTag() == p2->getTag())
			return true;
		else
			return false;
	}
	//changed to accept smart pointer
	bool sharedSearchPetPredicate(std::shared_ptr<Pet_T> p1, std::shared_ptr<Pet_T> p2)
	{
		// to be finished, if the search generic algorithm is used
		//modified, added functionality for "search" generic algorithm
		if (p1->getTag() == p2->getTag())
			return true;
		else
			return false;
	}

	
	//above could use this for "search" algorithm, could just say if p1==p2 to return
	bool operator ==(Pet_T p1, Pet_T p2) 
	{
		return(p1.getTag() == p2.getTag());
	}

	///////////////////////////  Cat_T Implementation
	// Default
	Cat_T::Cat_T() {};

	// Cat_T implementation
	Cat_T::Cat_T(string p_name, string p_tag, string p_illness) : Pet_T(p_name, p_tag, p_illness) {};
	
	void Cat_T::whoAmI() const 
	{
		cout << "My name is " << name << ". I am a cat. My tag is: " << tag << endl<< "and I'm in the pet hospital because of " << illness<< endl;
	}


	////make this for dog and make it work?
	//void Cat_T::healAndSpeak() const
	//{
	//	std::string Healed = "Healed";
	//	//this->setIllness(Healed);
	//	std::cout << "Meoouuuuu" << std::endl;
	//}
	// Hair Ball!
	void Cat_T::hairBall() {
		cout << "Meouuuuuuuuw" << endl;
		cout << "Hair ball!" << endl;
	}

	///////////////// Dog_T implementation
	// Default
	Dog_T::Dog_T() {};

	Dog_T::Dog_T(string p_name, string p_tag, string p_illness) : Pet_T(p_name, p_tag, p_illness) { };

	void Dog_T::whoAmI() const 
	{
		cout << "My name is " << name << ". I am a dog. My tag is: " << tag << endl<< "and I'm in the pet hospital because of " << illness << endl;
	}

	void Dog_T::squirrel() 
	{
		cout << "AWROOOOOO" << endl;
		cout << "Squirrel!" << endl;
	}
	
	///////////// Bag Implementation

	// Bag exceptions
	Bag_E::Bag_E(string p_error_message) {
		errorMessage = p_error_message;
	};
	void Bag_E::handleError() {
		cout << errorMessage << endl;
		//  Other processing, maybe logging etc.
	};

	// Contructor to sets size of Bag
	Bag_T::Bag_T(unsigned p_capacity) {
		pets.reserve(p_capacity);
	};

	// Copy constructor: creates new object as a copy p_bag.  Objects make noise when copied
	Bag_T::Bag_T(const Bag_T& p_bag) 
	{
		pets.reserve(p_bag.getCapacity());		

		for (unsigned i = 0; i < p_bag.getSize(); i++) {
						
			Cat_T* catPointer = NULL;
			Dog_T* dogPointer = NULL;

			// To find which derived type of object needs to be copied
			// Runtime Type Identification (RTTI)
			catPointer = dynamic_cast<Cat_T*>(p_bag.pets[i]);
			dogPointer = dynamic_cast<Dog_T*>(p_bag.pets[i]);

			if (catPointer != NULL)
			{				
				pets.push_back(new Cat_T(*catPointer));
				catPointer->hairBall();
			}
			else 
			if (dogPointer != NULL)
			{				
				pets.push_back(new Dog_T(*dogPointer));
				dogPointer->squirrel();
			}
		}
	}

	//overloaded = assignment operator
	void Bag_T::operator = (const Bag_T& source)
	{
		int bag1Size = this->getSize();
		//removes the entire contents of bag 1
		for (int deleting = 0; deleting < bag1Size; deleting++)
		{
			this->pets.pop_back();
		}
		//adds the contents of bag 2 to bag 1
		pets.reserve(source.getCapacity());
		for (int count = 0; count < source.getSize(); count++)
		{
			Cat_T* catPtr = nullptr;
			Dog_T* dogPtr = nullptr;
			catPtr = dynamic_cast<Cat_T*>(source.pets[count]);
			dogPtr = dynamic_cast<Dog_T*>(source.pets[count]);
			if (catPtr != nullptr)
			{
				this->pets.push_back(new Cat_T(*catPtr));
				catPtr->hairBall();   //speak
			}
			else if (dogPtr != nullptr)
			{
				this->pets.push_back(new Dog_T(*dogPtr));
				dogPtr->squirrel();
			}

		}
	}
	// Destructor
	Bag_T::~Bag_T() {
		for(unsigned int i = 0; i < pets.size(); i++) {
			delete pets[i];
		}
	};

	size_t Bag_T::getCapacity() const {
		return pets.capacity();
	}

	size_t Bag_T::getSize() const {
		return pets.size();
	}	


	//add function utilizing the "Factory" class
	//user chooses type of pet to add at the menu and the pet factory creates it in class PetFactory
	void Bag_T::addPet(std::string petType, PetPtr newPet) throw (Bag_E)
	{

		if (pets.size() < pets.capacity())
			pets.push_back(PetFactory::NewPet(petType, newPet));
		else
			throw(Bag_E("Hospital is at capacity"));
	}


	// Adds Pet to Bag
	//void Bag_T::addPet(PetPtr p_pet) throw (Bag_E) 
	//{

	//	if (pets.size() < pets.capacity())
	//		pets.push_back(p_pet);
	//	else				
	//		throw(Bag_E("Bag is full"));
	//}



	//for demo purposes only.  would usually have while loop to read entire file
	//void Bag_T::readFile()
	//{
	//	PetPtr newPet;
	//	newPet = new Cat_T;
	//	std::ifstream instream("petHospital.txt");
	//	std::string name, tag, illness;

	//	std::getline(instream >> std::ws, name);
	//	newPet->setName(name);
	//	std::getline(instream >> std::ws, tag);
	//	newPet->setTag(tag);
	//	std::getline(instream >> std::ws, illness);
	//	newPet->setName(illness);
	//	try
	//	{
	//		addPet(newPet);
	//	}
	//	catch (Bag_E e)
	//	{
	//		e.handleError();
	//	}

	//	PetPtr newPet2;
	//	newPet = new Dog_T;

	//	std::getline(instream >> std::ws, name);
	//	newPet2->setName(name);
	//	std::getline(instream >> std::ws, tag);
	//	newPet2->setTag(tag);
	//	std::getline(instream >> std::ws, illness);
	//	newPet2->setName(illness);
	//	try
	//	{
	//		addPet(newPet2);
	//	}
	//	catch (Bag_E e)
	//	{
	//		e.handleError();
	//	}
	//	instream.close();
	//}
	// Sort Bag.  
	// Uses STL "sort", containter's iterator, and a predicate function to compare elements
	void Bag_T::sortPets() 
	{
		// How to pass in a sort predicate, a non-member.  It is a function pointer that is being passed
		sort(pets.begin(), pets.end(), sortPetPredicate);
		// How to pass in a sort predicate, a static member.  It needs an & to become an address of the method
		sort(pets.begin(), pets.end(), &sortPetPredicate_member);
	}
	

	//
	void Bag_T::findAndReleasePet()
	{	

		//restored remove functionality with the normal pet pointers.
		PetPtr whatPet = new Pet_T;
		cin >> *whatPet;
		PetPtr a[1] = { whatPet };	//create an iterator for PetPtr
		//using generic search algorithm instead of manual search
		//std::search (where to start search iterator, end search iterator, bounds of what to search for iterator, end bound of what to search for iterator, predicate)
		where = (std::search(pets.begin(), pets.end(), a, a + 1, searchPetPredicate));		
		if (where != pets.end())
		{
			std::cout << "Pet found, releasing pet" << std::endl;
			pets.erase(where);
		}
		else
			std::cout << "Pet not found" << std::endl;

		//smart pointer for extra credit
		//with smart pointer - this would actually work on the project if the add pet function used the vector of shared pointers, but since the pets are added as petPtr, this does nothing
		//std::unique_ptr <Pet_T> whatPet ( new Pet_T);
		std::shared_ptr <Pet_T> sharedWhatPet(new Pet_T);
		//cin >> *sharedWhatPet;

		std::shared_ptr<Pet_T> b[1] = { sharedWhatPet };
		//generic search algorithm used
		sharedWhere = (std::search(sharedPets.begin(), sharedPets.end(), b, b+1, sharedSearchPetPredicate));
		if (sharedWhere!=sharedPets.end())
		{
			std::cout << "Pet found, releasing pet" << std::endl;
			sharedPets.erase(sharedWhere);
		}
		//else
			//std::cout << "Pet not found" << std::endl;


		//  Invoke "search" generic algorithm DONE
		//  ...
		//std::vector<PetPtr>::iterator it;
		//int bagSize = pets.size();
		//PetPtr a[1] = { whatPet };	//create an iterator for PetPtr
		//std::unique_ptr<Pet_T> a[1] = { whatPet };
	
		//// Manual find - replace with generic algorithm "search"
		//for (where = pets.begin(); where != pets.end(); where++)
		//{

		//	// Check if equal using == operator on Pet_T
		//	if ((**where) == (*whatPet))
		//	{

		//		std::cout << "Releasing " << *whatPet << std::endl;
		//		break;
		//	}
		//}
		//// Found it, so now release
		//if (where != pets.end())
		//	pets.erase(where);
		//else
		//	cout << "Pet not found! \n";
	}
	
	
	// Release Cats
	void Bag_T::releaseCats() 
	{
		Cat_T* catPointer = NULL;
		for (unsigned i = 0; i < pets.size(); i++)
		{			
			// To find whether basePointer is pointing to which Derived type of object
			// Runtime Type Identification (RTTI)
			catPointer = dynamic_cast<Cat_T*>(pets[i]);
			if (catPointer != NULL)  // It is a Cat!
			{
				catPointer->hairBall();
				delete pets[i];
				pets.erase(pets.begin() + i);
				i--;
			}
		}
	}

	// Release Dogs
	void Bag_T::releaseDogs() 
	{
		Dog_T* dogPointer = NULL;
		for (unsigned i = 0; i < pets.size(); i++)
		{
			// To find whether basePointer is pointing to which Derived type of object
			// Runtime Type Identification (RTTI)
			dogPointer = dynamic_cast<Dog_T*>(pets[i]);
			if (dogPointer != NULL)  // It is a dog!
			{
				dogPointer->squirrel();
				delete pets[i];
				pets.erase(pets.begin() + i);
				i--;
			}
		}
	}
		
	ostream& operator <<(ostream& outs, const Bag_T& the_object)
		//Overloads the << operator for output values of type Bag_T.
		//Precondition: If outs is a file output stream, then outs has already been
		//connected to a file.
	{
		if (the_object.pets.size() == 0)
			outs << "The bag is empty" << endl;

		for (unsigned i = 0; i < the_object.pets.size(); i++) 
		{
			outs << *(the_object.pets[i]);
		};
		
		return outs;
	}

} // namespace csci2312