#include <iostream>
#include <string>

class Tree
{
	private:
		std::string nodeData;
	public:
		Tree *leftNode;
		Tree *rightNode;
		Tree *parentNode;

		Tree(std::string s)
		{
			nodeData = s;
			Tree *parentNode = 0;
			Tree *leftNode = 0;
			Tree *rightNode = 0;
		}

		Tree * addLeftNode(std::string s)
		{
			Tree *t = new Tree(s);
			t->parentNode = this;
			leftNode = t;
			return t;
		}

		Tree * addRightNode(std::string s)
		{
			Tree *t = new Tree(s);
			t->parentNode = this;
			rightNode = t;
			return t;
		}

		void giveParent(Tree *parent)
		{
			parentNode = parent;
		}

		int evaulate()
		{
			if(parentNode == 0)
			{
				//perform acts of magic and wonderment
				return 1;
			} else
			{
				std::cout<<"not parent node, something wrong\n";
				return 0; //dunno what to do for returning here
			}
		}
};

//Initially parser will only do the opperations: + - * / and ()
void numberState(char x, bool *error)
{
	std::cout<<"number state and char is: "<<x<<std::endl;
}

void symbolState(char x, bool *error)
{
	std::cout<<"symbol state and char is: "<<x<<std::endl;
}

int main(){
	std::string eq;
	std::cout<<"enter equation less than 100 characters with no spaces\n";
	std::cin>>eq;
	bool error = (eq[0] > 47 && eq[0] < 58) || eq[0] == '(' ? 0 : 1;//make sure equation starts right
	if(error)
		std::cout<<"equation must start with a number or a (\n";
	int currentState;
	int i = 0;
	//FSM loop
	while(!error)
	{
		//check for end of equation
		if(i == eq.length())
		{
			std::cout<<"end of equation\n";
			error = 1;
		}

		if(!error)
		{
			//determine state of FSM
			if(eq[i] > 47 && eq[i] < 58)
				currentState = 0;
			else if((eq[i] > 39 && eq[i] < 44) || eq[i] == 45 || eq[i] == 47)
				currentState = 1;
			else
			{
				std::cout<<"invalid character: "<<eq[i]<<std::endl;
				error = 1;
			}
		}

		if(!error)
		{
			//execute state
			switch(currentState)
			{
				case 0:
					numberState(eq[i], &error);
					break;
				case 1:
					symbolState(eq[i], &error);
					break;
			}
		}
		i++;
	}
}
