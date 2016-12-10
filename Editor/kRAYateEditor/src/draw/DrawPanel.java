/*
 * @author JToolenDCU date 17th March '16
 * @text	updated 18-3-16
 * 			Class for the drawing to take place
 */
package draw;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
//import JPanel
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.MatteBorder;

import staticThings.StaticVars;

public class DrawPanel extends JPanel {
	//serialize to keep state of class in memory
	private static final long serialVersionUID = 1L;
	
	public DrawPanel(){
		//draw a grid
		drawGrid();
				
		//init colour
		setOpaque(true);
		//setBackground(Color.WHITE);
		
		//listeners
		//dpl = new DrawPanelListener(this);
		//addMouseListener(dpl);
		//addMouseMotionListener(dpl);
	}
	//method to display a grid on the panel
	void drawGrid(){
		setLayout(new GridBagLayout());

        GridBagConstraints gbc = new GridBagConstraints();
        for (int row = 0; row < 64; row++) {
            for (int col = 0; col < 64; col++) {
                gbc.gridx = col;
                gbc.gridy = row;

                CellPane cellPane = new CellPane();
                Border border = null;
                if (row < 63) {
                    if (col < 63) {
                        border = new MatteBorder(1, 1, 0, 0, StaticVars.defaultBorder);
                    } else {
                        border = new MatteBorder(1, 1, 0, 1, StaticVars.defaultBorder);
                    }
                } else {
                    if (col < 63) {
                        border = new MatteBorder(1, 1, 1, 0, StaticVars.defaultBorder);
                    } else {
                        border = new MatteBorder(1, 1, 1, 1, StaticVars.defaultBorder);
                    }
                }
                cellPane.setBorder(border);
                add(cellPane, gbc);
            }
        }
	}

}
