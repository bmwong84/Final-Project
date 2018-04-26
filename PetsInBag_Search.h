//Bryant Wong
//CSCI2312 Final Project

//Interface File for Bag of Pets

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace csci2312
{
	using std::string;
	using std::ostream;
	using std::istream;
	using std::cout;
	using std::endl;
	using std::cin;
	using std::vector;

	// FINAL PROJECT FEATURE - class hierarchy
	// Base Class with all the listed components 
	class Pet_T
	{
	public:
		// Dafault Constructor		
		Pet_T();

		// Constructor sets Pet's name and unique tag
		Pet_T(string tag, string name, string illness);		

		// Destructor
		~Pet_T();		
				
		// Accessors and Mutators
		void setName(string);
		string getName() const;

		void setTag(string);
		string getTag() const;

		void setIllness(std::string);
		string getIllness() const;

		// FINAL PROJECT FEATURE - virtual method
		// Pet introduces himself. A virtual method: the derived classes will redefine it
		void virtual whoAmI() const;


		////heal the pet's illness and they thank you by speaking
		//void virtual healAndSpeak() const;
		
		//virtual ~Pet_T() {};

		// FINAL PROJECT FEATURE 
		// Overloads the >> operator for input values of type Pet_T	
		friend istream& operator >>(istream& ins, Pet_T& the_object);
			//Precondition: If ins is a file input stream, then ins has already been
			//connected to a file.

		// FINAL PROJECT FEATURE 
		// Overloads the << operator for output values of type Pet_T.
		friend ostream& operator <<(ostream& outs, const Pet_T& the_object);
			//Precondition: If outs is a file output stream, then outs has already been
			//connected to a file.		
	
	protected:
		// FINAL PROJECT FEATURE - unique attribute on a base class			
		// Uniquely identifies the elements in the container
		string tag;

		string name;		

		string illness;
	};

	// FINAL PROJECT FEATURE - Pointer and type alias
	// Use 'typedef' to define a new type for the pointer to the base element
	typedef Pet_T* PetPtr;

	// FINAL PROJECT FEATURE - generic "sort" predicate for order
	// Function to support generic "sort"	
	// Returns true if pet pointed to by the first pointer is 'lesser' (whatever it means) 
	// than a pet pointed to by the second pointer 
	bool sortPetPredicate(PetPtr left, PetPtr right);

	// FINAL PROJECT FEATURE - generic "search" predicate for equality
	// Function to support generic "search"	
	// Returns true if pet pointed to by the first pointer is 'equal' (whatever it means) 
	// to a pet pointed to by the second pointer 
	bool searchPetPredicate(PetPtr left, PetPtr right);
	bool sharedSearchPetPredicate(std::shared_ptr<Pet_T> left, std::shared_ptr<Pet_T> right);
	//{
	//	return (left->getTag() == right->getTag());
	//}

	
	// FINAL PROJECT FEATURE
	// Two sub-classes

	class Cat_T : public Pet_T 
	{
		public:
			// Default
			Cat_T();

			// Constructor sets Cat's name and tag
			Cat_T(string tag, string name, string illness);
			
			// FINAL PROJECT FEATURE - virtual method redefined
			// Pet introduces himself: "My name is <name>.  I am a cat."
			void virtual whoAmI() const override;
			virtual ~Cat_T(){};
			//void virtual healAndSpeak() const override;	//speaks 
			// FINAL PROJECT FEATURE - unique to sub-class
			// Hair Ball!
			void hairBall();
	};

	class Dog_T : public Pet_T {
		public:
			// Default
			Dog_T();

			// Constructor sets Dog's name and tag
			Dog_T(string name, string tag, string illness);

			// FINAL PROJECT FEATURE - virtual method redefined
			// Pet introduces himself: "My name is <name>.  I am a dog."
			void virtual whoAmI() const override;
			virtual ~Dog_T() {};
			//void virtual healAndSpeak() const override;
			// FINAL PROJECT FEATURE - unique on a sub-class
			// Squirrel!
			void squirrel();
	};

	//for "factory" method.  used to add whatever class of pet that is admitted to the hospital
	class PetFactory
	{
	public:
		static Pet_T *NewPet(std::string petType, PetPtr petPointer=nullptr)
		{
			Pet_T newPet;
			if (petType == "Dog" && petPointer ==nullptr)
			{
				cin >> newPet;
				return new Dog_T(newPet.getName(), newPet.getTag(), newPet.getIllness());		//returns a dog pointer with the info passed in from the pet
			}
			else if (petType == "Dog" && petPointer != nullptr)
			{
				return new Dog_T(petPointer->getName(), petPointer->getTag(), petPointer->getIllness());
			}
			if (petType == "Cat"&& petPointer==nullptr)
			{
				cin >> newPet;
				return new Cat_T(newPet.getName(), newPet.getTag(), newPet.getIllness());		//returns a cat pointer with the info passed in from the pet
			}
			else if (petType == "Cat" && petPointer != nullptr)
			{
				return new Cat_T(petPointer->getName(), petPointer->getTag(), petPointer->getIllness());
			}
			return nullptr;
		}
	};

	// FINAL PROJECT FEATURE - Exception
	// Bag exceptions
	class Bag_E 
	{
	private:
		string errorMessage;
	public:
		//  Constructor set a message
		Bag_E(string); 
		void handleError();
	};

	// FINAL PROJECT FEATURE - Abstraction
	// Bag container abstraction.  Holds an STL container
	// All features are required

	class Bag_T {
	  public:
		  
		  // Default Contructor to sets Bag's capacity
		  Bag_T(unsigned=MAX_CAPACITY);

		  // FINAL PROJECT FEATURE - copy constructor
		  // Copy Constructor 
		  Bag_T(const Bag_T&);

		  // FINAL PROJECT FEATURE - destructor
		  // Destructor
		  ~Bag_T();

		  size_t getCapacity() const;
		  size_t getSize() const;

		  // FINAL PROJECT FEATURE - Polymorphism
		  // Adds a Pet to Bag, passsing the base pointer.  
		 // void addPet(PetPtr) throw (Bag_E);
		  void addPet(std::string, PetPtr) throw (Bag_E);
		  
		  void readFile();

		  // FINAL PROJECT FEATURE - Generic Algorithm
		  // Sort Pets
		  void sortPets();

		  //static bool sortPetPredicate_member(PetPtr, PetPtr);

		  // FINAL PROJECT FEATURE - Generic Algorithm
		  // Find and Relese a Pet
		  void findAndReleasePet();
		  		  		  
		  // Release Cats
		  void releaseCats();

		  // Release Dogs
		  void releaseDogs(); 	 
		  		  
		  // FINAL PROJECT FEATURE - Function Template
		  // Template function to release pets - replaces two above methods
		  // Invocation will plug in a specific pet type 		  
		  template<typename PetType_T> void releasePets() 
		  {
			  // Identify a template opportunity in your project, code goes here

			  //removes the generic pet from the bag, whether dog or cat
			  PetType_T* petPointer = nullptr;
			  for (unsigned count = 0; count < pets.size(); count++)
			  {
				  petPointer = dynamic_cast<PetType_T*>(pets[count]);
				  if (petPointer != nullptr)
				  {
						//pet speak petPointer->???  make generic speak?
					  delete pets[count];
					  pets.erase(pets.begin() + count);
					  count--;
				  }
			  }
		  };

		  // FINAL PROJECT FEATURE
		  // Overloaded assignment operator - EXTRA CREDIT
		   void operator =(const Bag_T& source);

		  // FINAL PROJECT FEATURE
		  friend ostream& operator <<(ostream& outs, const Bag_T& the_object);
		  //Overloads the << operator for output content of type Bag_T.
		  //Precondition: If outs is a file output stream, then outs has already been
		  //connected to a file.


	private:
		int static MAX_CAPACITY;

		// Generic sort predicate as a member function, same logic as in the non-member example
		// Must be a static method, as the generic sort function will not have a Bag's object instance
		static bool sortPetPredicate_member(PetPtr, PetPtr);

		// FINAL PROJECT FEATURE - STL container
		// A vector container is used to hold pointers to pets.  This will practice polymorphism
		vector<PetPtr> pets;  
		vector<std::shared_ptr<Pet_T> > sharedPets;		//for smart ptr
		//vector<std::shared_ptr<Pet_T> > pets;		//for smart ptr

		// FINAL PROJECT FEATURE - Iterator
		// We need an iterator on the vector, in order to use STL functions, such as sort.  
		// An iterator is a generic concept to let us visit the elements of the container 
		vector<PetPtr>::iterator where;
		vector<std::shared_ptr<Pet_T>>::iterator sharedWhere;		//for smart ptr
			
	};

} // namespace csci2312
