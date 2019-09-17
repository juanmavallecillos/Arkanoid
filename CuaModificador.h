#include "NodeModificador.h"

class CuaModificador
{
public:
	CuaModificador();
	~CuaModificador();
	void afegeix(Modificador& valor);
	void treu();
	Modificador &getPrimer() const;
	Modificador &getUltim() const;
	bool esBuida() const;
	NodeModificador* getNode() const;

private:
	NodeModificador* m_primer;
	NodeModificador* m_ultim;
};