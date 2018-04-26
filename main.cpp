//Bryant Wong
//CSCI2312 Final Project

// ***************************************************************************************
//  This program models a bag with pets to demonstrate polymorphism
//  It holds a vector of pointers to a generic Pet, but specific pets are added 
//  STL vector container is used, and also a vector's iterator
//  Template method is used to release specific types of Pets
//  Generic algorithm "sort" is used.  It demonstrates use of iterators and a Ordering predicate
//  Generic algorithm "search" needs to be written.  It demonstrates use of iterators and an Equality predicate
// ***************************************************************************************


#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "PetsInBag_Search.h"
#include <fstream>

using namespace csci2312;


// ======================
//     main function
// ======================
int main()
{
	//  Instantiate the container with given capacity
	Bag_T bag(5);
	
	//  Generic pointer used to add items
	PetPtr newPet;

	string pet_name;
	int choice = -1;

	// Main Menu
	while (choice != 0)  // not a bullet proof data entry, enhancements welcome
	{
		cout << endl;		
		cout << "Welcome to the Pet Hospital" << endl;
		cout << "0) Quit" << endl;
		cout << "1) Admit cat for treatment" << endl;
		cout << "2) Admit dog for treatment" << endl;
		cout << "3) Print list of all patients" << endl;
		cout << "4) Heal and discharge all cats" << endl;
		cout << "5) Heal and discharge all dogs" << endl;
		cout << "6) Sort Pets by ID tag number" << endl;
		cout << "7) Find, heal, and discharge a Pet" << endl;
		cout << "8) Read data from a file" << endl;
		cout << "9) Discharge all pets" << endl;

		cin >> choice;
		while (std::cin.fail())
		{
			std::cout << "Invalid entry.  Please Enter a number" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> choice;
		}
		PetPtr newPet2;
		std::ifstream instream("petHospital.txt");
		std::string name, tag, illness, petType;
		switch (choice) 
		{ 			     

		case 1:  
			cout << "Enter Cat's Name, Tag, and Illness: " << std::endl;;
			// Uses input operator to read in info about a pet
			//newPet = new Cat_T;
			//cin >> *newPet;
			petType = "Cat";
			try 
			{
				bag.addPet(petType, nullptr); // Polymorphism: addPet is defined to add generic Pet_T, but passes in Cat_T
			}
			catch (Bag_E e) 
			{
				e.handleError();
			}
			break;
		case 2: 			
			// Uses input operator to read in info about a pet
			//newPet = new Dog_T;
			//cout << "Enter Dog's Name, Tag, and Illness: "<< std::endl;
			//cin >> *newPet;
			petType = "Dog";
			try 
			{
				//adding pet also calls "PetFactory" class function "NewPet" to turn out the correct type of pet that is admitted
				bag.addPet(petType, nullptr); // Polymorphism: addPet is defined to add generic Pat_T, but passes in Dog_T
			}
			catch (Bag_E e) 
			{
				e.handleError();
			}
			break;
		case 3: 
			// Prints content of Bag
			cout << bag;  
			break;
		case 4:
			//  Release all the Cats

			//  Dedicated method
			//bag.releaseCats();

			//DONE**********************
			// FINAL PROJECT FEATURE - invoke function template
			// Template method - needs to be implemented
			 bag.releasePets<Cat_T>();

			break;
		case 5:
			//  Release all the Dogs

			//  Dedicated method			
			//bag.releaseDogs();

			//DONE***************************************
			// FINAL PROJECT FEATURE - invoke function template
			// Template method - needs to be implemented
			 bag.releasePets<Dog_T>();


			break;
		case 6:
			// Sort the bag
			bag.sortPets();
			break;

		case 7:		
			//  Asks for a search target, finds and removes the item
			cout << "Enter Pet's information: " << std::endl;;
			bag.findAndReleasePet();
			break;
		case 8:
			//bag.readFile();
			//for demo purposes only, would normally call a function with while loop to read until end of file
			std::cout << "Reading demo file" << std::endl;
			newPet = new Cat_T;
			std::getline(instream >> std::ws, name);
			newPet->setName(name);
			std::getline(instream >> std::ws, tag);
			newPet->setTag(tag);
			std::getline(instream >> std::ws, illness);
			newPet->setIllness(illness);
			try
			{
				bag.addPet("Cat", newPet);
			}
			catch (Bag_E e)
			{
				e.handleError();
			}


			newPet2 = new Dog_T;

			std::getline(instream >> std::ws, name);
			newPet2->setName(name);
			std::getline(instream >> std::ws, tag);
			newPet2->setTag(tag);
			std::getline(instream >> std::ws, illness);
			newPet2->setIllness(illness);
			try
			{
				bag.addPet("Dog", newPet2);
			}
			catch (Bag_E e)
			{
				e.handleError();
			}
			instream.close();
			break;
		case 9:
			//releases all pets from hospital, whther they are cats or dogs
			bag.releasePets<Pet_T>();
			break;
		default:
			break;
		};
		
	}

	// Copy constructor demo
	std::cout << "Copy Constructor Demo" <<std::endl;
	std::cout << "Contents of original bag" << std::endl;
	std::cout << bag;
	std::cout << "Copying contents of bag" << std::endl;
	Bag_T new_bag = Bag_T(bag);
	std::cout << "Contents of copied bag" << std::endl;
	cout << new_bag;

	// Assignment demo
	cout << "Assignment Demo" << endl;
	Bag_T bag1 = Bag_T(2);
	bag1.addPet("Cat", new Cat_T("Fluffy", "123", "Furr loss"));
	bag1.addPet("Cat", new Cat_T("Sleepy", "345", "Blind eye"));
	cout << "Content of Bag1:" << endl;
	cout << bag1;

	Bag_T bag2 = Bag_T(3);
	bag2.addPet("Dog", new Dog_T("Rufus", "560", "Heartworms"));
	bag2.addPet("Dog", new Dog_T("Sasha", "777", "Hip Dysplasia"));
	bag2.addPet("Dog", new Dog_T("Misha", "555", "Broken Leg"));
	cout << "Content of Bag2:" << endl;
	cout << bag2;

	//DONE***************
	// Make sure the assignment operator is overloaded! Needs code - EXTRA CREDIT
	 cout << "Now assigning bag1 = bag2 " << endl;
	 bag1 = bag2;
	 cout << "Content of Bag1:" << endl;
	 cout << bag1;
	

	system("pause");

	return 0;
}

