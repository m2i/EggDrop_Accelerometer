// Egg Drop Egg
// Matthew E. Nelson
// August 2014
// Revision 1

// Based on Parametric egg by
// Nicholas C. Lewis 2011
// http://www.thingiverse.com/thing:7832

radius=35;		//radius of egg
stretch = 1.7;	//amount of "stretch" in the top half
angle = 90;		//angle of egg (0 is vertical, 90 is on side)
base = 2;	  //Sets how far down for base, max 2.4.  Nominal 2

fn = 150;

function get_offset(a) = lookup(a, [[0, cos(45)],[60, cos(90)],[90, cos(70)]]);

//Egg side A
difference(){
intersection(){
	echo(get_offset(angle));
	translate([0,0,83])cube(base*stretch*radius, center = true);
	translate([0,0,get_offset(angle)*radius])rotate([angle,0,0]){
		union(){
			intersection(){
				//translate([0,0,0])cube(90, center = true);
				scale([1,1,stretch])sphere(r=radius, $fn=fn);
				translate([0,0,stretch*radius])cube(2*stretch*radius, center = true);
				//translate([0,-40,0])cube(90, center = true);
			}
			sphere(r=radius, $fn=fn);
			
		}
	}
//translate([0,0,5])cube(40, center = true);
}
translate([0,-8,18])cube([34.5,47.5,20], center = true);
//T-lock
translate([-5,-40,18])cube([5,10,25], center = true);
translate([0,-40,18])cube([10,5,20], center = true);
translate([0,-40,28])cube([10,10,5], center = true);

translate([-5,22,18])cube([5,10,20], center = true);
translate([0,22,18])cube([10,5,20], center = true);
translate([0,22,27])cube([10,10,3], center = true);
}

//Egg side B
rotate([0,180,0]){
difference(){
intersection(){
	echo(get_offset(angle));
	translate([0,0,83])cube(base*stretch*radius, center = true);
	translate([0,0,get_offset(angle)*radius])rotate([angle,0,0]){
		union(){
			intersection(){
				//translate([0,0,0])cube(90, center = true);
				scale([1,1,stretch])sphere(r=radius, $fn=fn);
				translate([0,0,stretch*radius])cube(2*stretch*radius, center = true);
				//translate([0,-40,0])cube(90, center = true);
			}
			sphere(r=radius, $fn=fn);
			
		}
	}
//translate([0,0,5])cube(40, center = true);
}
translate([0,-8,18])cube([34.5,47.5,20], center = true);

}
//T-lock
difference(){
translate([0,-40,23])cube([5,10,8], center = true);
translate([0,-36,23])cube([10,5,5], center = true);
translate([0,-44,23])cube([10,5,5], center = true);
}
difference(){
translate([0,22,23])cube([5,10,8], center = true);
translate([0,26,23])cube([10,5,5], center = true);
translate([0,18,23])cube([10,5,5], center = true);
}
}