#include <iostream>
#include <string>

class Tree
{
	public:
		Tree *leftNode;
		Tree *parentNode;
		Tree *rightNode;
		std::string nodeData;

		Tree(std::string s)
		{
			nodeData = s;
			parentNode = 0;
			leftNode = 0;
			rightNode = 0;
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

		double evaulate()
		{
            try{
		        if(parentNode == 0){
		    		return evalHelper(this);
		    	}else{
		    		throw 0;
		    	}
            }catch(int i){
				std::cout<<"not parent node\n";
            }
            return 0;
		}
		
		double evalHelper(Tree *t)
		{
			std::string data = t->nodeData;
            try
            {
			    if(!(data == "+" || data == "-" || data == "*" || data == "/"))
			    {
			    	int num = stoi(data);
			    	return (double)num;
			    }
			    switch(data[0])
			    {
			    	case '+':
			    	{
			    		return evalHelper(t->leftNode) + evalHelper(t->rightNode);
			    	}
			    	case '-':
			    	{
			    		return evalHelper(t->leftNode) - evalHelper(t->rightNode);
			    	}
			    	case '*':
			    	{
			    		return evalHelper(t->leftNode) * evalHelper(t->rightNode);
			    	}
			    	case '/':
			    	{
			    		return evalHelper(t->leftNode) / evalHelper(t->rightNode);
			    	}
                    default:
                    {
                        throw -1;
                    }
			    }
            }catch(int e){
                std::cout<<"invalid data in tree: "<<data<<std::endl;
                return 0;
            }
		}

		void checkAndPrint()
		{
			if(parentNode != 0){
				printf("not parentNode\n");
				return;
			}
			std::cout<<"parent: "<<nodeData<<std::endl;
			printTree(*this);
		}

		void printTree(Tree t)
		{
			if(t.leftNode != 0){
				std::cout<<"left: "<<t.leftNode->nodeData<<std::endl;
                printTree(*(t.leftNode));
			}
			if(t.rightNode != 0){
				std::cout<<"right: "<<t.rightNode->nodeData<<std::endl;
                printTree(*(t.rightNode));
			}
		}

        void printGraph(std::string beforeR, std::string beforeL) {
            bool right = (rightNode != 0) ? true : false;
            bool left = (leftNode != 0) ? true : false;
            std::cout<<nodeData<<"\n";
            bool first = (beforeR.compare("") == 0) ? true : false;
            if (right) {
                int rightC = rightNode->countChildren();
                if (left) {
                    std::cout<<beforeR<<"|->";
                } else {
                    std::cout<<beforeR<<"`->";
                }
                if (first) {
                    beforeR = "|  ";
                } else {
                    beforeR += "|  ";
                }
                rightNode->printGraph(beforeR, beforeR);
            }
            if (left) {
                std::cout<<beforeL<<"`->";
                beforeL += "   ";
                leftNode->printGraph(beforeL, beforeL);
            }
        }

        int countChildren() {
            if (leftNode == 0 && rightNode == 0) return 1;
            if (leftNode != 0 && rightNode != 0) return 1 + rightNode->countChildren() + leftNode->countChildren();
            if (leftNode != 0) return 1 + leftNode->countChildren();
            if (rightNode != 0) return 1 + rightNode->countChildren();
            return -1000000;
        }
};

int main()
{
	std::string eq;
	std::cout<<"enter equation less than 100 characters with no spaces\n";
	std::cin>>eq;
	bool error = (eq[0] > 47 && eq[0] < 58) || eq[0] == '(' ? 0 : 1;//make sure equation starts right
	if(error)
		std::cout<<"equation must start with a number or a (\n";

	//variables for FSM
	Tree *currentNode;
	Tree *parent;
    Tree *paraNode;
	bool firstNode = true;
	int currentState;
	int i = 0;
	int numParaIn = 0;
	std::string number = "";
	//FSM loop
	while(!error)
	{
		//check for end of equation
		if(i == eq.length())
		{
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
			switch(currentState)
			{
				case 0:
				{
					number.append(std::string(1,eq[i]));
					break;
				}
				case 1:
				{
					if(eq[i] == '(' || eq[i] == ')')
					{
					}
					char opperation = eq[i];
					switch(eq[i])
					{
						case '+':
						case '-':
						{
							if(firstNode)
							{
								parent = new Tree(number);
								number = "";
								firstNode = false;
							}
							if(number != "")
							{
								currentNode->addRightNode(number);
								number = "";
							}
							Tree *temp = new Tree(std::string(1, opperation));
							temp->leftNode = parent;
							parent->giveParent(temp);
							parent = temp;
							currentNode = temp;
							break;
						}
						case '*':
						case '/':
						{
							if(firstNode)
							{
								parent = new Tree(std::string(1, opperation));
								currentNode = parent;
								parent->addLeftNode(number);
								firstNode = false;
								number = "";
								break;
							}
							currentNode = currentNode->addRightNode(std::string(1, opperation));
							break;
						}
					}
					
					if(number != "")
					{
						currentNode->addLeftNode(number);
						number = "";
					}
					break;
				}
			}
			if(i == eq.length()-1 && currentState == 0)
			{
				if(firstNode)
				{
					parent = new Tree(number);
					break;
				}
				currentNode = currentNode->addRightNode(number);
			}
		}
		i++;
	}
	std::cout<<std::fixed<<parent->evaulate()<<"\n";
    parent->printGraph("", "");
}
