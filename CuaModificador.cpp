#include "CuaModificador.h"

// Constructor
CuaModificador::CuaModificador()
{
	m_primer = NULL;
	m_ultim = NULL;
}

// Destructor
CuaModificador::~CuaModificador()
{
	while (!esBuida())
	{
		treu();
	}
}

// Retorna "true" si la cua es buida
bool CuaModificador::esBuida() const
{
	return m_primer == NULL;
}

// Retorna el primer modificador de la cua
Modificador &CuaModificador::getPrimer() const
{
	return m_primer->getValor();
}

// Retorna l'ultim modificador de la cua
Modificador &CuaModificador::getUltim() const
{
	return m_ultim->getValor();
}

// Afegeix un nou modificador a la cua
void CuaModificador::afegeix(Modificador &valor)
{
	NodeModificador* aux;

	aux = new NodeModificador;
	aux->setValor(valor);
	aux->setNext(NULL);

	if (esBuida())
	{
		m_primer = aux;
		m_ultim = aux;
	}
	else
	{
		m_ultim->setNext(aux);
		m_ultim = aux;
	}
}

// Treu el primer modificador de la cua
void CuaModificador::treu()
{
	NodeModificador* aux;

	aux = m_primer;
	if (m_primer == m_ultim)
	{
		m_ultim = NULL;
	}
	m_primer = aux->getNext();
	delete aux;
}

// Retorna el Node del primer modificador de la llista
NodeModificador* CuaModificador::getNode() const
{
	return m_primer;
}