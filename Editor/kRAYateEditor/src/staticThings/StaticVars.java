/*
 * @author JamesToolenDCU 18th March '16
 * @text	class for Static variables colour
 */

package staticThings;

import java.awt.Color;
import java.io.IOException;
import java.nio.file.LinkOption;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.swing.JOptionPane;

@SuppressWarnings("unused")
public class StaticVars {
	
	public static int  levelWorked = 0;
	public static String shapeType = "square", fileName = "LevelErr", pPath;
	public static Color shapeColor = Color.WHITE, defaultBorder = Color.GRAY;
	public static boolean shapeFilled = false;
	public static boolean mouseDrag = false;
	public static Color defaultBackground = new Color(254,0,0);
	public static String destinationLevelPath, destinationSettingsPath, launchPath;
	
	public static void setPaths(){
		do{
			levelWorked = Integer.parseInt( JOptionPane.showInputDialog("Please enter the Level number are you working on?"));
		}while(levelWorked == 0);
		pPath = ClassLoader.getSystemClassLoader().getResource(".").getPath();
		pPath = pPath.substring(1);
		setDestinationLevelPath();//Paths.get(pPath));
		setDestinationSettingsPath();//Paths.get(pPath));
		setLaunchPath();//Paths.get(pPath));
	}
	
	public static String getLaunchPath() {
		return launchPath;
	}
	
	public static void setLaunchPath() {
		StaticVars.launchPath = "./resources/Burgerworm/kRAYatePlayer.exe";
	}
	public static String getDestinationLevelPath() {
		return destinationLevelPath;
	}
	public static void setDestinationLevelPath() {
		StaticVars.destinationLevelPath = "resources/Burgerworm/Data/Levels/";
	}
	public static String getDestinationSettingsPath() {
		return destinationSettingsPath;
	}
	public static void setDestinationSettingsPath() {
		StaticVars.destinationSettingsPath = "resources/Burgerworm/gameData.ini";
	}
}
