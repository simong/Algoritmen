package bordspel;

/**
 * @author wijnand.schepens@hogent.be
 */
public interface Handler {
	/**
	 * Deze methode wordt door <code>BordspelVenster</code> opgeroepen indien
	 * de gebruiker op een vak van het spelbord klikt met de muis.
	 *
	 * @param i      de "x"-coordinaat van het vak waarin geklikt is (links is 0)
	 * @param j      de "y"-coordinaat van het vak waarin geklikt is (bovenaan is 0)
	 * @param knop   geeft aan met welke muisknop er geklikt is (1=linkermuisknop)
	 * @param aantal geeft aan hoeveel keer er geklikt werd (1 voor gewone klik of 2 voor dubbelklik)
	 */
	void klik(int i, int j, int knop, int aantal);

	/**
	 * Deze methode wordt door <code>BordspelVenster</code> opgeroepen indien
	 * de gebruiker een toets van het klavier indrukt.
	 *
	 * @param toetsCode een code die aangeeft over welke toets het gaat.
	 * De klasse <code>java.awt.event.KeyEvent</code> bevat een lijst van constanten
	 * voor toestcodes, zoals <code>VK_SPACE</code>, <code>VK_ENTER</code> enz.
	 *
	 *
	 * @see java.awt.event.KeyEvent
	 */
	void toets(int toetsCode);

	/**
	 * Deze methode wordt door <code>BordspelVenster</code> opgeroepen bij
	 * elke tik van de timer.
	 */
	void klokTik();
}
