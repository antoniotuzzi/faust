#include "xtended.hh"
#include "Text.hh"
#include <math.h>

class AtanPrim : public xtended
{

 public:
 
 	AtanPrim() : xtended("atan") {}
	
	virtual int 	arity () { return 1; }
	
	virtual bool	needCache ()	{ return true; }
	
	virtual Type 	infereSigType (const vector<Type>& args)
	{
		assert (args.size() == 1);
		return floatCast(args[0]);
	}
	
	virtual void 	sigVisit (Tree sig, sigvisitor* visitor) {}	
	
	virtual int infereSigOrder (const vector<int>& args) {
		return args[0];
	}

	
	virtual Tree	computeSigOutput (const vector<Tree>& args) {
		num n;
		if (isNum(args[0],n)) {
			return tree(atanf(float(n)));
		} else {
			return tree(symbol(), args[0]);
		}
	}
		
	virtual string 	generateCode (Klass* klass, const vector<string>& args, const vector<Type>& types)
	{
		return subst("atanf($0)", args[0]);
	}
	
};


xtended* gAtanPrim = new AtanPrim();

