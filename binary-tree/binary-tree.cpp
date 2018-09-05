#include <iostream>

using namespace std;

class Node
{
public:
	Node();
	bool insert_node(Node* _node);
	bool insert_value(int _value);
	int get_value() { return value;}
	void print_pre_order();
	void print_in_order();
	void print_past_order();
	Node* find_by_value(int _value);
	Node* find_in_node_by_value(int _value);
	void delete_from_parent();
	void print_as_tree();
	~Node();
private:
	Node* left;
	Node* right;
	Node* parent;
	int value;
};

Node::Node()
{
	left = NULL;
	right = NULL;
	parent = NULL;
	value = 0;
}

bool Node::insert_node(Node* _node)
{
	if (_node->value < this->value)
	{
		if (left == NULL)
		{
			left = _node;
			left->parent = this;
		} else {
			left->insert_node(_node);

		}
		return 1;
	} else if (_node->value > this->value)
	{
		if (right == NULL)
		{
			right = _node;
			right->parent = this;
		} else {
			right->insert_node(_node);

		}
		return 1;
	}
	return 0;
}

bool Node::insert_value(int _value)
{
	if (_value > 0)
	{
		value = _value;
	}
}

void Node::print_pre_order()
{
	if (left != NULL)
	{
		left->print_pre_order();
	}

	if (value != 0)
	{
		cout<<this->value<<"\t";
	}

	if (right != NULL)
	{
		right->print_pre_order();
	}
}

void Node::print_in_order()
{

	if (value != 0)
	{
		cout<<this->value<<"\t";
	}

	if (left != NULL)
	{
		left->print_in_order();
	}

	if (right != NULL)
	{
		right->print_in_order();
	}
}

void Node::print_past_order()
{
	if (right != NULL)
	{
		right->print_past_order();
	}

	if (left != NULL)
	{
		left->print_past_order();
	}

	if (value != 0)
	{
		cout<<this->value<<"\t";
	}

}

Node* Node::find_by_value(int _value)
{
	if (left != NULL)
	{
		if (left->find_in_node_by_value(_value) != NULL)
		{
			return left->find_in_node_by_value(_value);
		}
	}
	if (right != NULL)
	{
		if (right->find_in_node_by_value(_value) != NULL)
		{
			return right->find_in_node_by_value(_value);
		}
	}
	if (value == _value)
	{
		return this;
	}

	return NULL;
}

Node* Node::find_in_node_by_value(int _value)
{
	if (left != NULL)
	{
		if (left->find_in_node_by_value(_value) != NULL)
		{
			return left->find_in_node_by_value(_value);
		}
	}
	if (right != NULL)
	{
		if (right->find_in_node_by_value(_value) != NULL)
		{
			return right->find_in_node_by_value(_value);
		}
	}
	if (value == _value)
	{
		return this;
	}

	return NULL;
}

void Node::delete_from_parent()
{
	if (parent == NULL)
	{
		return;
	}
	if (parent->left == this)
	{
		parent->left = NULL;
		return;
	}
	if (parent->right == this)
	{
		parent->right = NULL;
		return;
	}
	return;
}

void Node::print_as_tree()
{
	if (parent != NULL)
	{
		parent->print_as_tree();
	}
	cout<<(parent != NULL?"-": "")<<value;
}

Node::~Node()
{
	if (left != NULL)
	{
		delete left;
	}
	if (right != NULL)
	{
		delete right;
	}
}

void insert_value_page(Node* _node)
{   cout<<" 0. Back"<<endl<<endl;
	int value;
	do
	{
		cin>>value;
		if (_node->get_value() == 0)
		{
			_node->insert_value(value);
		} else {
			Node* tmp_node = new Node();
			tmp_node->insert_value(value);
			_node->insert_node(tmp_node);
		}
		cout<<"OK"<<endl<<endl;

	} while (value != 0);
}

void find_value_page(Node* _node)
{
	cout<<" 0. Back"<<endl<<endl;
	int value;
	do
	{
		cin>>value;

		Node* result = _node->find_by_value(value);
		if (result != NULL)
		{
			cout<<"Value Found "<<endl;
			result->print_as_tree();
			cout<<endl<<endl;
		} else {
			cout<<"Value not Found"<<endl<<endl;
		}

	} while (value != 0);
}

void delete_by_value_page(Node* _node)
{
	cout<<" 0. Back"<<endl<<endl;
	int value;
	cin>>value;
	while (value != 0)
	{
		Node* result = _node->find_by_value(value);
		if (result != NULL)
		{
			result->delete_from_parent();
			delete result;
			cout<<"Node Deleted"<<endl<<endl;
		} else {
			cout<<"Node with this Value not Found"<<endl<<endl;
		}
		cin>>value;
	}
}

int main()
{
	Node* node = new Node();
	int input;
	do
	{
		cout<<"1. Insert Value"<<endl
		<<"2. Display PreOrder"<<endl
		<<"3. Display InOrder"<<endl
		<<"4. Display PastOrder"<<endl
		<<"5. Find Value"<<endl
		<<"6. Delete Value"<<endl
		<<endl
		<<"0. Exit"<<endl;

		cin>>input;
		switch(input)
		{
			case 1:
			    cout<<endl;
				insert_value_page(node);
				cout<<endl<<endl<<endl;
				break;
			case 2:
				node->print_pre_order();
				cout<<endl<<endl<<endl;
				break;
			case 3:
				node->print_in_order();
				cout<<endl<<endl<<endl;
				break;
			case 4:
				node->print_past_order();
				cout<<endl<<endl<<endl;
				break;
			case 5:
				cout<<endl;
				find_value_page(node);
				cout<<endl<<endl<<endl;
				break;
			case 6:
				cout<<endl;
				delete_by_value_page(node);
				cout<<endl<<endl<<endl;
				break;
			default:
				break;
		}
	} while(input != 0);
	return 0;
}
