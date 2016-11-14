#include <iostream>
#include <memory>

using namespace std;
class Machine
{
  class State *current;
  public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void on();
    void off();
};

class State
{
  public:
    virtual void on(Machine *m)
    {
        cout << "   already ON\n";
    }
    virtual void off(Machine *m)
    {
        cout << "   already OFF\n";
    }
};

void Machine::on()
{
  current->on(this);
}

void Machine::off()
{
  current->off(this);
}


class ON: public State
{
public:
  	static ON * Instance()
  	{
  		if(m==NULL)
  			m = new ON();
  		return m;
  	}
    void off(Machine *m);
private:
	static ON* m;
	ON()
	{}
};

class OFF: public State
{
  public:
  	static OFF * Instance()
  	{
  		if(m==NULL)
  			m = new OFF();
  		return m;
  	}
  	void on(Machine *m);
private:
	static OFF* m;
	OFF()
	{}
};

Machine::Machine()
{
  current = OFF::Instance();
  cout << '\n';
}

void OFF::on(Machine *m)
{
    cout << "   going from OFF to ON\n";
    m->setCurrent(ON::Instance());
}

void ON::off(Machine *m)
{
  cout << "   going from ON to OFF\n";
  m->setCurrent(OFF::Instance());
}

// initialize
OFF* OFF::m = new OFF();
ON* ON::m = new ON();

int main()
{

  Machine fsm;
  int num;
  while (1)
  {
    cout << "Enter 0/1: ";
    cin >> num;
    if(num == 1)
    	fsm.on();
    else if(num == 0)
    	fsm.off();
  }
}
