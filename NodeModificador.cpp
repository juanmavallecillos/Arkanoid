#include "NodeModificador.h"

// Retorna valor del node
Modificador& NodeModificador::getValor()
{
	return m_valor;
}

// Retorna posici� del seg�ent node
NodeModificador* NodeModificador::getNext() const
{
	return m_next;
}

// Guarda valor
void NodeModificador::setValor(Modificador& valor)
{
	m_valor = valor;
}

// Guarda Next
void NodeModificador::setNext(NodeModificador*next)
{
	m_next = next;
}