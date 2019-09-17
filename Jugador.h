const int MAX_SIZE_NOM_JUGADOR = 15;

class Jugador
{
public:
	Jugador();
	~Jugador();
	void setNom(char nom[]);
	void setPunts(int punts);
	void getNom(char *nom) const;
	int getPunts() const;

private:
	char m_nom[MAX_SIZE_NOM_JUGADOR];
	int m_punts;
};