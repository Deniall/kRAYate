/**
 * @author	JToolenDCU date: 17th March'16
 * @text	A class for the main menu and its components
 */
package menus;
//import graphics, Actionlistener, file IO
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.JFileChooser;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.filechooser.FileNameExtensionFilter;

import dialog.SettingDialog;
import draw.DrawPanel;
import main.MainFrame;
import staticThings.StaticVars;

public class MainMenu extends JMenuBar{
	//serialize to keep state of class in memory
	private static final long serialVersionUID = 1L;
	
	private MainFrame mf;
	
	//menu file items
	//private JMenuItem newAction = new JMenuItem("New...");
	//private JMenuItem openAction = new JMenuItem("Open...");
	private JMenuItem saveAction = new JMenuItem("Save");
	private JMenuItem saveAsAction = new JMenuItem("Save As...");
	private JMenuItem exitAction = new JMenuItem("Exit");
	
	/**menu edit items
	private JMenuItem undoAction = new JMenuItem("Undo");
	private JMenuItem redoAction = new JMenuItem("Redo");
	private JMenuItem cutAction= new JMenuItem("Cut");
	private JMenuItem copyAction = new JMenuItem("Copy");
	private JMenuItem pasteAction = new JMenuItem("Paste");
	*/
	//game settings items
	private JMenuItem editSettingsAction = new JMenuItem("Edit Game Settings");
	
	/**menu image items
	private JMenuItem resizeImgAction = new JMenuItem("Resize image");
	private JMenuItem resizeCanvasAction = new JMenuItem("Resize Canvas");
	private JMenuItem turn90ClockAction = new JMenuItem("Rotate 90' clockwise");
	private JMenuItem turn90CounterAction = new JMenuItem("Rotate 90' counter clockwise");
	private JMenuItem rotate180Action = new JMenuItem("Rotate 180'");
	*/
	//launch item
	private JMenuItem launchAction = new JMenuItem("Launch Your Game");
	
	public MainMenu(MainFrame mf){
		
		this.mf = mf; 
		//build menus
		JMenu fileMenu = new JMenu("File");
		//JMenu editMenu = new JMenu("Edit");
		JMenu settingsMenu = new JMenu("Settings");
		//JMenu imageMenu = new JMenu("Image");
		JMenu launchMenu = new JMenu("Launch");
		
		//add menus
		this.add(fileMenu);
		//this.add(editMenu);
		this.add(settingsMenu);
		//this.add(imageMenu);
		this.add(launchMenu);
		
		
		//add menu items to menu
		
		//file
		//fileMenu.add(newAction);
		//fileMenu.add(openAction);
		fileMenu.add(saveAction);
		fileMenu.add(saveAsAction);
		fileMenu.addSeparator();
		fileMenu.add(exitAction);
		
		/**edit
		editMenu.add(undoAction);
		editMenu.add(redoAction);
		editMenu.addSeparator();
		editMenu.add(cutAction);
		editMenu.add(copyAction);
		editMenu.add(pasteAction);
		*/
		//game settings
		settingsMenu.add(editSettingsAction);
		/*
		settingsMenu.add(gameScreenSizeAction);
		settingsMenu.add(playerPosAction);
		settingsMenu.add(playerSpeedAction);
		*/
		/**image
		imageMenu.add(resizeImgAction);
		imageMenu.add(resizeCanvasAction);
		imageMenu.addSeparator();
		imageMenu.add(turn90ClockAction);
		imageMenu.add(turn90CounterAction);
		imageMenu.add(rotate180Action);
		*/
		//launch settings
		launchMenu.add(launchAction);
		
		//initiate listeners
		initFileActions();
		//initEditActions();
		initSettingsActions();
		//initImageActions();
		initLaunchActions();
	}
	
	private void initSettingsActions(){
		editSettingsAction.addActionListener(new ActionListener(){

			@Override
			public void actionPerformed(ActionEvent e) {
				new SettingDialog(mf).setVisible(true);
			}
			
		});

	}
	
	/*
	 * @text add function to listeners and declare abstract methods
	 */

	private void initFileActions(){
		
		saveAction.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				save();
			}
		});
		/*
		 * @text save method for saving to png, jpg or jpeg
		 */
		saveAsAction.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				DrawPanel p = mf.getDrawPanel();
				int w = p.getWidth();
				int h = p.getHeight();
				
				BufferedImage bi = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
				Graphics2D g2d = bi.createGraphics();
				p.paint(g2d);
				
				JFileChooser chooser = new JFileChooser();
				
				chooser.addChoosableFileFilter(new FileNameExtensionFilter(
						"PNG (.png)", "png"));
				chooser.addChoosableFileFilter(new FileNameExtensionFilter(
						"JPG (.jpg)", "jpg"));
				chooser.addChoosableFileFilter(new FileNameExtensionFilter(
						"JPEG (.jpg)", "jpeg"));
				chooser.setFileFilter(chooser.getChoosableFileFilters()[1]);
				
				int r = chooser.showSaveDialog(mf);
				
				if(r == JFileChooser.APPROVE_OPTION){
					File out = chooser.getSelectedFile();
					
					String ext = out.getName().substring(out.getName().lastIndexOf(".")+ 1);
					
					if(ext.equalsIgnoreCase("png") || ext.equals("jpg") || ext.equals("jpeg")){
						try{
							ImageIO.write(bi, "png", out);
						}catch(IOException e1){
							e1.printStackTrace();
						}
					}else{
						JOptionPane.showMessageDialog(null, "Wrong extension", "Error", JOptionPane.ERROR_MESSAGE);
					}
				}
				
			}
		});
		
		
		/*
		 * @text exit program
		 */
		exitAction.addActionListener(new ActionListener(){
			
			@Override
			public void actionPerformed(ActionEvent e){
				System.exit(0);//in future check if saved
			}
		});

	}
	
	private void initLaunchActions(){
		launchAction.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e){
				save();
				String cmd = "resources/Burgerworm/kRAYatePlayer.exe";
				try{
					Process p = new ProcessBuilder(cmd).start();
					p.waitFor();
				} catch (IOException e1) {
					JOptionPane.showMessageDialog(null, e1.getStackTrace());
				} catch (InterruptedException e1) {
					JOptionPane.showMessageDialog(null, e1.getStackTrace());
				}
			}
		});
	}

	void save(){
		DrawPanel p = mf.getDrawPanel();
		int w = p.getWidth();
		int h = p.getHeight();
		
		BufferedImage bi = new BufferedImage(w, h, BufferedImage.TYPE_INT_RGB);
		Graphics2D g2d = bi.createGraphics();
		p.paint(g2d);
		
		resize(bi, getDirectory(), 64, 64);
	}
	
	public static void resize(BufferedImage bi, String outputImagePath, int scaledWidth, int scaledHeight){
		 try {
			// reads input image
	        BufferedImage inputImage = bi;
	 
	        // creates output image
	        BufferedImage outputImage = new BufferedImage(scaledWidth, scaledHeight, inputImage.getType());
	 
	        // scales the input image to the output image
	        Graphics2D g2d = outputImage.createGraphics();
	        g2d.drawImage(inputImage, 0, 0, scaledWidth, scaledHeight, null);
	        g2d.dispose();
	 
	        // extracts extension of output file
	        String formatName = outputImagePath.substring(outputImagePath.lastIndexOf(".") + 1);
	 
	        // writes to output file
			ImageIO.write(outputImage, formatName, new File(outputImagePath));
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
	
	String getDirectory(){
		StaticVars.fileName =  "/Level" +StaticVars.levelWorked + ".png";
		return StaticVars.getDestinationLevelPath() + StaticVars.fileName;
	}
}



