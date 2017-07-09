// Egg Drop Egg
// Matthew E. Nelson
// July 2017
// Revision 4

// Based on Parametric egg by
// Nicholas C. Lewis 2011
// http://www.thingiverse.com/thing:7832

radius=34;		//radius of egg
stretch = 1.9;	//amount of "stretch" in the top half
angle = 90;		//angle of egg (0 is vertical, 90 is on side)
base = 2;	  //Sets how far down for base, max 2.4.  Nominal 2
cutout = 3; //Sets the depth of the cutout in the egg

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
//This cuts out the opening for our circuit board
translate([-18,-42,17])#sensor_cutout();
//T-lock
//translate([-5,-45,18])cube([6,11,20], center = true);
//translate([0,-45,18])cube([10,5,20], center = true);
//translate([0,-45,27])cube([11,11,3], center = true);

//translate([-5,23,18])cube([6,11,20], center = true);
//translate([0,23,18])cube([10,5,20], center = true);
//translate([0,23,27])cube([11,11,3], center = true);
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
//This cuts out the opening for our circuit board
//translate([0,-8,26])#cube([34.5,47.5,cutout], center = true);
//Light Pipe
//translate([9,-11,-15])#cylinder(h = 70,r=3.1,$fn=fn);

//This cuts out the opening for our circuit board
translate([-18,-42,17])#sensor_cutout();
//This cuts out the opening for the switch
translate([25,-10,20.5])#switch_cutout();
}
//T-lock
//difference(){
//translate([0,-40,23])cube([5,9,8.5], center = true);
//translate([0,-36,23])cube([10,4,4], center = true);
//translate([0,-44,23])cube([10,4,4], center = true);
//}
//difference(){
//translate([0,23,23])cube([5,9,8.5], center = true);
//translate([0,27,23])cube([10,5,4], center = true);
//translate([0,19,23])cube([10,5,4], center = true);
//}
}


module sensor_cutout(){
    //Below defines the dimensions for the sensor module
    xdim = 37;
    ydim = 65;
    zdim = 10;
    rdim = 3;
    hull(){
        translate([rdim,rdim,0])cylinder(r=rdim,h=zdim);
        translate([xdim-rdim,rdim,0])cylinder(r=rdim,h=zdim);
        translate([rdim,ydim-rdim,0])cylinder(r=rdim,h=zdim);
        translate([xdim-rdim,ydim-rdim,0])cylinder(r=rdim,h=zdim);
    }
}

module switch_cutout(){
    //Define the dimensions of the switch, in this case Adafruit #805
    xdim = 17;
    ydim = 12;
    zdim = 5;
    cube([xdim,ydim,zdim],true);
}