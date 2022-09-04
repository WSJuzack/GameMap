### General Information

Gamelab II requirements were  to create a plugin/ package for Unity or Unreal, which helps developers with the game development process.
This year we also had external stakeholders, which proposed the projects to us.
With my partner Tobias Böhler, we chose this topic because AI is very important in the games industry. Working
with one of the most modern methods was a very good way for us to get up to date knowledge on this subject.

Like in the previous project documentation,  the trailer, poster and report for this project are in the "presentation" folder.
 
## Abstract

A tool for the user to paint their height maps in a simple editor. 
This sketch will then be turned into a believable height map via our GAN.

## Repository Usage Guides

How to use our package: 1. Unzip our 'GAN package.zip' in the repositories builds folder.
				2. Create a unity project.
				3. Add the GAN package in the package manage from disk.
				4. Import the samples.
				5. Copy the 'requirements.txt' file from the unziped GAN package folder inside the repositories builds folder.
				6. Go to the project settings folder of your unity project and paste the 'requirements.txt' file there.
				7. Restart your unity project, this will install all necessary python libraries.
				8. Now inside your unity project, open the 
				   'Assets\Samples\GAN for adaptive terrain generation\1.0.0\TerrainSample\DrawMeshFull.unity' scene.
				9. A window will pop up to import TextMeshPro, you will have to import the TMP Essentials.
				   (Pressing play will maybe leave the buttons blank, just stop unity and press play again.)
				10. Press play and enjoy.

General usage:		Height maps will be saved in the 'Assets' folder of your unity project.
				To use them in your own projects, we recommend the untiy terrain toolbox
				to get a 3D version of your height map.

! The Python for Unity API is still in a experimental state, this leads to some Unity crashing bugs, we were not able to resolve !
! It will always work on the first time you press play in the Unity Editor, but it will crash once you stop and start playing again !
			





