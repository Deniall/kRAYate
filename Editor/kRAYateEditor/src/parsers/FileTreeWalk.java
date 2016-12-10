/**
 * @author	JToolenDCU date: 17th March'16
 * @text	
 */
package parsers;

import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;

public class FileTreeWalk{
	
	public FileTreeWalk(Path path){
		if(path == null){
			//System.out.println("usage: FileTreeWalk <source-path>");
			System.exit(-1);
		}
		Path pathSource = path;
		try{
			Files.walkFileTree(pathSource, new MyFileVisitor());
		}catch(IOException e){
			e.printStackTrace();
		}
	}

}

class MyFileVisitor extends SimpleFileVisitor<Path>{
	public FileVisitResult visitFile(Path path, BasicFileAttributes fileAttributes){
		//System.out.println("file name: " + path.getFileName());
		return FileVisitResult.CONTINUE;
	}
	public FileVisitResult preVisitDirectory(Path path,BasicFileAttributes fileAttributes){
		//System.out.println("-----------Directory name: " + path + "--------------");
		return FileVisitResult.CONTINUE;
	}
}