package doolhof;

import bordspel.BordspelVenster;
import bordspel.Handler;

import javax.swing.Icon;
import java.awt.Color;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.util.HashMap;
import java.util.Random;

/**
 * @author wijnand.schepens@hogent.be
 */
public class Doolhof implements Handler
{
	private int[][] cellen;	
	private Point doelPos;
	private Point pionPos;

	private final int VRIJ = 0;
	private final int MUUR = -1;
	private final int ONTPLOFT = -2;
	private final int DOEL = -3;
	private final int PION = -4;

	private HashMap<Integer, Icon> figuren = new HashMap<Integer, Icon>();
	private BordspelVenster venster;


	public static void main(String[] args) throws Exception
	{
		new Doolhof();
	}

	public Doolhof() throws Exception
	{
		int breedte = 20;
		int hoogte = 10;
		this.cellen = new int[breedte][hoogte];
		for (int i=0; i<getBreedte(); i++)
			for (int j=0; j<getHoogte(); j++)
				cellen[i][j] = VRIJ;
		Random random = new Random();
		for (int i=0; i<100; i++)
			cellen[random.nextInt(breedte)][random.nextInt(hoogte)] = MUUR;

		pionPos = new Point(random.nextInt(breedte), random.nextInt(hoogte));
		cellen[pionPos.x][pionPos.y] = PION;

		figuren.put(VRIJ, BordspelVenster.maakFiguur(50, 50, Color.LIGHT_GRAY));
		figuren.put(MUUR, BordspelVenster.maakFiguur(50, 50, Color.DARK_GRAY));
		figuren.put(ONTPLOFT, BordspelVenster.maakFiguur(50, 50, Color.RED));
		figuren.put(DOEL, BordspelVenster.maakFiguur(50, 50, Color.GREEN));
		figuren.put(PION, BordspelVenster.maakFiguur(50, 50, Color.BLUE));

		this.venster = new BordspelVenster("Doolhof", breedte, hoogte, figuren.get(VRIJ), 1000, this);

		this.venster.setStatus("status...");

		teken();
	}

	private void teken()
	{
		for (int i=0; i<getBreedte(); i++)
			for (int j=0; j<getHoogte(); j++)
			{
				int type = cellen[i][j];
				Icon figuur = figuren.get(type);
				if (figuur == null)
					figuur = figuren.get(VRIJ);
				venster.getVak(i, j).setFiguur(figuur);
				if (type > 0)
					venster.getVak(i, j).setTekst("" + type);
			}
			
	}

	public int getBreedte()
	{
		return cellen.length;
	}

	public int getHoogte()
	{
		return cellen[0].length;
	}
	

	public void klik(int i, int j, int knop, int aantal)
	{
//		System.out.println("klik op " + i + ", " + j + " met knop " + knop + " aantal:" + aantal);
		if (knop == 1)
		{
			setPionPos(new Point(i, j));
		}
		else
		{
			setDoelPos(new Point(i, j));
			// ...
		}
		teken();
	}

	public void toets(int toetsCode)
	{
		//System.out.println("toets " + toetsCode);
		if (toetsCode == KeyEvent.VK_SPACE)
		{
			// ...
		}
		else if (toetsCode == KeyEvent.VK_ENTER)
		{
			// ... 
		}
		teken();
	}

	public void klokTik()
	{
		// ...
	}
	
	private void setPionPos(Point p)
	{
		if (pionPos != null)
			cellen[pionPos.x][pionPos.y] = VRIJ;
		pionPos = p;
		cellen[pionPos.x][pionPos.y] = PION;
	}

	private void setDoelPos(Point p)
	{
		if (doelPos != null)
			cellen[doelPos.x][doelPos.y] = VRIJ;
		doelPos = p;
		cellen[doelPos.x][doelPos.y] = DOEL;
	}

	

}
