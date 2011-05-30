package bordspel;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.net.URL;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.Timer;
import javax.swing.UIManager;

/**
 * Eenvoudige klasse die instaat voor de visualisatie van een bordspel.
 * Een bordspel is een rechthoekig patroon vakken.
 * Elk vak wordt getekend als een figuur (<code>Icon</code>).
 *
 * De klasse zorgt ook voor het doorgeven van gebeurtenissen aan
 * een <code>Model</code>.
 * <ul>
 * <li>toetsindruk
 * <li>muisklik
 * <li>timer-tik
 * </ul>
 *
 * @author wijnand.schepens@hogent.be
 */
public class BordspelVenster 
{
	private JFrame frame;
	private Handler handler;
	private Vak[][] vakken;
	private JLabel statusVeld;

	/** 
	 * Maakt een BordspelVenster bestaande uit <code>breedte</code> x <code>hoogte</code> vakken.
	 * In elk vak wordt <code>initFiguur</code> getoond.
	 * De grootte van elk vak is gelijk aan de grootte van <code>initFiguur</code>, en dit kan niet
	 * meer wijzigen, tenzij via de methode <code>reset()</code>.
	 *
	 * Er wordt een timer gestart die elke <code>tikTijd</code> "tikt".
	 * Alle gebeurtenissen (toetsindruk, muisklik en kloktik) worden aan
	 * <code>afhandelaar</code> doorgegeven.
	 *
	 * @param titel         titel van het spel.
	 * @param breedte       breedte van het speelbord (aantal vakken).
	 * @param hoogte        hoogte van het speelbord (aantal vakken).
	 * @param initFiguur    <code>Icon</code> waarmee de vakken initieel getekend worden.
	 * @param tikTijd       tijd in milliseconden tussen twee tikken van de timer.
	 * @param afhandelaar   object dat instaat voor de afhandeling van gebeurtenissen.
	 *
	 * @see import javax.swing.Icon
	 */
    public BordspelVenster(String titel, int breedte, int hoogte, Icon initFiguur, final int tikTijd, final Handler afhandelaar)
	{
		this.frame = new JFrame(titel);
		
		this.handler = afhandelaar;

		reset(breedte, hoogte, initFiguur);
		
		java.awt.EventQueue.invokeLater(new Runnable()
		{
			public void run()
			{
				frame.addKeyListener(new KeyAdapter()
				{
					@Override
					public void keyPressed(KeyEvent e)
					{
						afhandelaar.toets(e.getKeyCode());
					}
				});
				Timer timer = new Timer(tikTijd, new ActionListener()
				{
					public void actionPerformed(ActionEvent e)
					{
						afhandelaar.klokTik();
					}
				});
				frame.setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
				frame.setLocationRelativeTo(null);
				frame.setResizable(false);
				frame.setVisible(true);
				frame.pack();
				frame.setLocationRelativeTo(null);

				try {
					UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
				}
				catch(Exception e) {}
				
				timer.start();
			}
		});
	}

	/**
	 * Hertekening van het bord met nieuwe breedte, hoogte en initFiguur.
	 *
	 * @param breedte    (nieuwe) breedte van het spelbord (aantal vakken)
	 * @param hoogte     (nieuwe) hoogte van het spelbord (aantal vakken)
	 * @param initFiguur <code>Icon<code> waarmee alle vakken hertekend worden.
	 */
	public void reset(int breedte, int hoogte, Icon initFiguur)
	{
		this.vakken = new Vak[breedte][hoogte];

		JPanel paneel = new JPanel();
		paneel.setLayout(new BorderLayout());

		JPanel bordpaneel = new JPanel();
		bordpaneel.setLayout(new GridLayout( hoogte, breedte));
		for (int j=0; j<hoogte; j++)
			for (int i=0; i<breedte; i++)
			{
				Vak vak = new Vak(i, j, handler);
				vak.setFiguur(initFiguur);
				//vak.setTekst("x");
				this.vakken[i][j] = vak;
				bordpaneel.add(vak);
			}
		paneel.add(bordpaneel, BorderLayout.CENTER);

		this.statusVeld = new JLabel("status...");
		this.statusVeld.setFocusable(false);
		this.statusVeld.setToolTipText(this.statusVeld.getText());
		paneel.add(statusVeld, BorderLayout.SOUTH);

		frame.setContentPane(paneel);

		frame.pack();
    }

	/**
	 * @return breedte van het spelbord (aantal vakken)
	 */
	public int getBreedte()
	{
		return vakken.length;
	}

	/**
	 * @return hoogte van het spelbord (aantal vakken)
	 */
	public int getHoogte()
	{
		return vakken[0].length;
	}


	public Vak getVak(int i, int j)
	{
		return vakken[i][j];
	}
	/**
	 * Toont <code>boodschap</code> in een (modaal) popup-venster.
	 */
	public void popup(String boodschap) {
		JOptionPane.showMessageDialog(frame, boodschap);
	}

	/**
	 * Toont <code>boodschap</code> in de statusbalk.
	 */
	public void setStatus(String boodschap) {
		this.statusVeld.setText(boodschap);
		this.statusVeld.setToolTipText(this.statusVeld.getText());
	}

	/**
	 * Hulpfunctie voor het maken van een rechthoekige <code>Icon</code>,
	 * gevuld met een gegeven <code>achtergrondkleur</code>.
	 *
	 * @param breedte         breedte (in pixels).
	 * @param hoogte          hoogte (in pixels).
	 * @param achtergrondkleur kleur waarmee de figuur opgevuld wordt.
	 *
	 * @return <code>ImageIcon</code> met gemaakte figuur.
	 *
	 * @see java.awt.Color
	 */
	public static Icon maakFiguur(int breedte, int hoogte, Color achtergrondkleur)
	{
		BufferedImage image = new BufferedImage(breedte, hoogte, BufferedImage.TYPE_INT_RGB);
		Graphics g = image.getGraphics();
		g.setColor(achtergrondkleur);
		g.fillRect(0, 0, breedte, hoogte);
		return new ImageIcon(image);
	}

	/**
	 * Hulpfunctie voor het inladen van een <code>Iconc</code> uit een
	 * "figuurbestand" (.jpg, .gif, .png, ...).
	 *
	 * @param pad pad naar figuurbestand.
	 * @return de ingeladen <code>ImageIcon</code>.
	 * @throws Exception indien laden niet gelukt is (bv. bestand niet gevonden).
	 */
	public static Icon laadFiguur(String pad) throws Exception
	{
		URL url = BordspelVenster.class.getResource(pad);
		if (url==null)
			throw new Exception("Kan figuur '" +pad + "' niet laden");
		return new ImageIcon(url);
	}


	public class Vak extends JLabel
	{
		private int i;
		private int j;

		public Vak(int i_, int j_, final Handler handler)
		{
			super("");
			this.i = i_;
			this.j = j_;
			this.setHorizontalTextPosition(JLabel.CENTER);
			this.setVerticalTextPosition(JLabel.CENTER);
			this.addMouseListener(new MouseAdapter()
			{
				@Override
				public void mouseClicked(MouseEvent e)
				{
					handler.klik(i, j, e.getButton(), e.getClickCount());
				}
			});
		}

		public void setTekst(String text)
		{
			this.setText(text);
		}

		public void setFiguur(Icon figuur)
		{
			this.setIcon(figuur);
		}
	}
}
