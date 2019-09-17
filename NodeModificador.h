#include "Modificador.h"

class NodeModificador
{
public:
	Modificador& getValor();
	NodeModificador* getNext() const;
	void setValor(Modificador& valor);
	void setNext(NodeModificador* next);

private:
	Modificador m_valor;
	NodeModificador* m_next;
};