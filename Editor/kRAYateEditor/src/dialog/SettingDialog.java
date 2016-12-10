/**
 * A game settings user interface to enable the user to record the  users choice of settings for their game
 * The user can choose between all that can affect the games play, Default values are provided.
 * The name of the level or levels number is decided from the start of the application but can be changed here
 * and is found in the StaticVars class
 * The size of the playing screen can be changed.
 * The players starting position in the game can be changed
 * The players speed can be changed
 * 
 * @author James Toolen
 * @version 4.3
 */

package dialog;

import javax.swing.JDialog;

import main.MainFrame;

import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JSpinner;

import javax.swing.JButton;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.io.File;
import java.awt.event.ActionEvent;
import javax.swing.JTextField;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import parsers.INITfile;
import staticThings.StaticVars;

public class SettingDialog extends JDialog{
	

	private static final long serialVersionUID = 1L;
	private JTextField scrWidthField;
	private JTextField scrHeightField;
	private JTextField startPosXField;
	private JTextField startPosYField;
	private JTextField levelField;
	private JSpinner playerSpeedspinner;
	private JButton saveBut;
	private JButton cancelBut;
	private INITfile ini;
	@SuppressWarnings("unused")
	private int scrWidth, scrHeight, startPosX, startPosY, level;
	private Double playerSpeed;
	
	public SettingDialog(MainFrame mf){
		
		setSize(300, 200);
		setTitle("Game Settings");
		setLocationRelativeTo(mf);
		this.setIconImage(Toolkit.getDefaultToolkit().getImage(StaticVars.pPath + "resources/Burgerworm/Data/images/iFAJ26P5.jpg"));
		getContentPane().setLayout(null);
		
		JLabel screenWidthLab = new JLabel("Game Screen Width: ");
		screenWidthLab.setBounds(10, 35, 134, 25);
		getContentPane().add(screenWidthLab);
		
		scrWidthField = new JTextField();
		scrWidthField.setText("640");
		scrWidthField.setBounds(188, 37, 86, 20);
		getContentPane().add(scrWidthField);
		scrWidthField.setColumns(4);
		scrWidth = Integer.parseInt(scrWidthField.getText());
		
		JLabel screenHeightLab = new JLabel("Game Screen Height: ");
		screenHeightLab.setBounds(10, 53, 134, 25);
		getContentPane().add(screenHeightLab);
		
		scrHeightField = new JTextField();
		scrHeightField.setText("512");
		scrHeightField.setBounds(188, 55, 86, 20);
		getContentPane().add(scrHeightField);
		scrHeightField.setColumns(4);
		scrHeight = Integer.parseInt(scrHeightField.getText());
		
		JLabel playerPosLab = new JLabel("Player Start Position: ");
		playerPosLab.setBounds(10, 71, 107, 25);
		getContentPane().add(playerPosLab);
		
		JLabel playerSpeedLab = new JLabel("Player Speed: ");
		playerSpeedLab.setBounds(10, 89, 107, 25);
		getContentPane().add(playerSpeedLab);
		
		JLabel startPosXLbl = new JLabel("X:");
		startPosXLbl.setBounds(127, 76, 17, 14);
		getContentPane().add(startPosXLbl);
		
		startPosXField = new JTextField();
		startPosXField.setText("32");
		startPosXField.setBounds(137, 73, 19, 20);
		getContentPane().add(startPosXField);
		startPosXField.setColumns(2);
		startPosX = Integer.parseInt(startPosXField.getText());
		
		JLabel startPosYLbl = new JLabel("Y:");
		startPosYLbl.setBounds(183, 76, 10, 14);
		getContentPane().add(startPosYLbl);
		
		startPosYField = new JTextField();
		startPosYField.setText("32");
		startPosYField.setColumns(2);
		startPosYField.setBounds(194, 73, 19, 20);
		getContentPane().add(startPosYField);
		startPosY = Integer.parseInt(startPosYField.getText());
		
		playerSpeedspinner = new JSpinner();
		playerSpeedspinner.setModel(new SpinnerNumberModel(new Double(0.8), new Double(0.8), new Double(1.2), new Double(0.05)));
		playerSpeedspinner.setBounds(144, 91, 49, 20);
		getContentPane().add(playerSpeedspinner);
		playerSpeed = (Double) playerSpeedspinner.getValue();
		
		cancelBut = new JButton("Cancel");
		cancelBut.setBounds(174, 125, 100, 25);
		getContentPane().add(cancelBut);
		
		saveBut = new JButton("Save");
		saveBut.setBounds(10, 125, 100, 25);
		getContentPane().add(saveBut);
		
		JLabel lblLevel = new JLabel("Level:");
		lblLevel.setBounds(10, 22, 46, 14);
		getContentPane().add(lblLevel);
		
		levelField = new JTextField();
		levelField.setText(Integer.toString(StaticVars.levelWorked));
		levelField.setBounds(188, 19, 86, 20);
		getContentPane().add(levelField);
		levelField.setColumns(10);
		level = Integer.parseInt(levelField.getText());
		
		initActions();
	}
	
	private void initActions(){
		
		levelField.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				setLevelField();
			}

		});
		
		scrWidthField.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				String text = (String) e.getSource();
				System.out.println(text);
				scrWidth = Integer.parseInt(text);
			}
		});
		
		scrHeightField.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				scrHeight = Integer.parseInt(scrHeightField.getText());
			}
		});
		
		startPosXField.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				startPosX = Integer.parseInt(startPosXField.getText());
			}
		});
		
		startPosYField.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				startPosY = Integer.parseInt(startPosYField.getText());
			}
		});
		
		playerSpeedspinner.addChangeListener(new ChangeListener(){
			
			@Override
			public void stateChanged(ChangeEvent e){
				playerSpeed = (Double) playerSpeedspinner.getValue();
			}

		});
		
		saveBut.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				try{
					ini = new INITfile(new File(getDirectory()));
				}catch(NullPointerException fnfe){
					JOptionPane.showMessageDialog(null, "Oi, who moved the file?");
				}
				JButton source = (JButton) e.getSource();
				if(source.isEnabled()){
					ini.addValue("[Game]", "playerSpeed", playerSpeed);
					ini.addValue("[Game]", "screenWidth", scrWidthField.getText());
					ini.addValue("[Game]", "screenHeight", scrHeightField.getText());
					ini.addValue("[Level" + levelField.getText() + "]", "playerX", startPosXField.getText());
					ini.addValue("[Level" + levelField.getText() + "]", "playerY", startPosYField.getText());
					ini.addValue("[Level" + levelField.getText() + "]", "texture", "Data/Levels/" + StaticVars.fileName + ".png");
					ini.addValue("[Level" + levelField.getText() + "]", "sprites", "Data/Levels/level3.csv" );
					ini.addValue("[Level" + levelField.getText() + "]", "spritesUsed", 3 );
					ini.addValue("[Level" + levelField.getText() + "]", "cieling", 4);
					ini.addValue("[Level" + levelField.getText() + "]", "floor", 3);
				}
				ini.save();
				dispose();
			}
		});
		
		cancelBut.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				dispose();
			}
		});
		
	}
	
	protected void setLevelField() {
		StaticVars.fileName = "Level" + levelField.getText();
	}

	String getDirectory(){
		return StaticVars.getDestinationSettingsPath();
	}
}
