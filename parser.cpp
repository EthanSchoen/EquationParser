#include <iostream>
#include <string>

class tree
{
	private:
		std::string nodeData;
	public:
		tree leftNode;
		tree rightNode;
		tree &parentNode = 0;

		tree(std::string s)
		{
			nodeData = s;
			&leftNode = 0;
			&rightNode = 0;
		}

		tree * addLeftNode(std::string s)
		{
			tree *t = new tree(s);
			t->parentNode = &this;
			leftNode = &t;
		}

		tree * addRightNode(std::string s)
		{
			tree *t = new tree(s);
			t->parentNode = &this;//compiler said ->, learn why
			rightNode = &t;
		}

		void giveParent(tree *parent)
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
