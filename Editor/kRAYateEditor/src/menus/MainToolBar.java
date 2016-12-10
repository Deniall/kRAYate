/*
 * @author JToolenDCU date: 17th March 16
 * @text A class for the maintoolbar and components
 */
package menus;
//import listeners
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
//import components
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JColorChooser;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JToolBar;
//import main frame and static variables
import main.MainFrame;
import staticThings.StaticVars;

public class MainToolBar extends JToolBar {
	//serialize to keep state of class in memory
	private static final long serialVersionUID = 1L;
	
	MainFrame mf;
	//build tool bar
	private JComboBox<String> combo;
	private JLabel comboLabel = new JLabel("Tool: ");
	
	private JLabel colorChoser = new JLabel("Colour: ");
	private JButton colorBut = new JButton("        ");
	
	private JCheckBox fillBox = new JCheckBox("Filled: ");
	
	private Color c = StaticVars.shapeColor;
	public MainToolBar(MainFrame mf){
		this.mf = mf;
		
		combo = new JComboBox<>();
		//combo.addItem("Square");
		//combo.addItem("Oval");
		//combo.addItem("Pencil");
		combo.addItem("Line");
		
		setOpaque(true);
		colorBut.setForeground(c);
		colorBut.setBackground(c);
		
		fillBox.setSelected(false);
		
		/*
		 * action Listener for selection in dropdown list
		 */
		combo.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				switch(combo.getSelectedIndex()){
					case 0:
						StaticVars.shapeType = "square";
						break;
					case 1:
						StaticVars.shapeType = "oval";
						break;
					case 2:
						StaticVars.shapeType = "pencil";
						break;
					case 3:
						StaticVars.shapeType = "line";
						break;
					default:
						StaticVars.shapeType = "square"; 
				}
			}
		});
		
		colorBut.addActionListener(new ActionListener(){
			/*
			 * (non-Javadoc)
			 * @see java.awt.event.ActionListener#actionPerformed(java.awt.event.ActionEvent)
			 * @text listener to create colour chooser and pick from a pallete
			 */
			@Override
			public void actionPerformed(ActionEvent e){
				c = JColorChooser.showDialog(MainToolBar.this, "Choose your colour", c);
				StaticVars.shapeColor = c;
				colorBut.setForeground(c);
				colorBut.setBackground(c);
			}
		});
		
		/*
		 * @text listener to show selected colour has been selected
		 */
		fillBox.addItemListener(new ItemListener(){

			@Override
			public void itemStateChanged(ItemEvent arg0) {
				StaticVars.shapeFilled = fillBox.isSelected();
			}
			
			
		});
		
		this.add(comboLabel);
		this.add(combo);
		//this.add(fillBox);
		this.add(colorChoser);
		this.add(colorBut);
	}

}
