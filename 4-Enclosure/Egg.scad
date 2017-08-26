// Egg Drop Egg
// Matthew E. Nelson
// July 2017
// Revision 4

// Based on Parametric egg by
// Nicholas C. Lewis 2011
// http://www.thingiverse.com/thing:7832

// Standoffs code from Steven Nemetz
// Current version: https://github.com/snemetz/OpenSCAD-Modules/tree/master/standoffs
// Customizable: http://www.thingiverse.com/thing:1528494

egg_radius=35;		//radius of egg
stretch = 1.9;	//amount of "stretch" in the top half
angle = 90;		//angle of egg (0 is vertical, 90 is on side)
base = 2;	  //Sets how far down for base, max 2.4.  Nominal 2
cutout = 3; //Sets the depth of the cutout in the egg

//Standoffs
//CUSTOMIZER VARIABLES

//Type of standoff(s) to generate
Generate = 2; // [1:Single, 2:Array-Same, 3:Array-Samples]
/* [Body] */
//Choose shape of the main body
Shape = 1; // [1:Round, 2:Square, 3:Hex]
//Select height of the main body,  mm
BaseHeight = 7; // [0:50]
//Select diameter of the main body, mm
BaseDia = 6; // [0:30]
/* [Top] */
//Choose style of the top section
Style = 4; // [1:Male, 2:Snap-In, 3:Flat, 4:Female, 5:Hollow]
//Select height of the top, mm
TopHeight = 4; // [2:20]
//Select diameter of the top, mm
TopDia = 2.5; // [1:25]
/* [Array Settings] */
//For array: Space between standoffs, X mm
X_Offset = 46; // [2:30]
//For array: Space between standoffs, Y mm
Y_Offset = 18; // [2:30]
//For Array-Same
Columns = 2;
//For Array-Same
Rows = 2;

//CUSTOMIZER VARIABLES END

/* [Hidden] */
// For sample array
Shapes = [1:3]; // All valid shapes
Styles = [1:5]; // All valid styles

RndFrags = 50; // number of facet fragments for round shapes

fn = 150;

function get_offset(a) = lookup(a, [[0, cos(45)],[60, cos(90)],[90, cos(70)]]);


//Egg side A
difference(){
intersection(){
	echo(get_offset(angle));
	translate([0,0,83])cube(base*stretch*egg_radius, center = true);
	translate([0,0,get_offset(angle)*egg_radius])rotate([angle,0,0]){
		union(){
			intersection(){
				//translate([0,0,0])cube(90, center = true);
				scale([1,1,stretch])sphere(r=egg_radius, $fn=fn);
				translate([0,0,stretch*egg_radius])cube(2*stretch*egg_radius, center = true);
				//translate([0,-40,0])cube(90, center = true);
			}
			sphere(r=egg_radius, $fn=fn);
			
		}
	}
//translate([0,0,5])cube(40, center = true);
}
//This cuts out the opening for our circuit board
translate([-18,-42,16])#sensor_cutout();
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
	translate([0,0,83])cube(base*stretch*egg_radius, center = true);
	translate([0,0,get_offset(angle)*egg_radius])rotate([angle,0,0]){
		union(){
			intersection(){
				//translate([0,0,0])cube(90, center = true);
				scale([1,1,stretch])sphere(r=egg_radius, $fn=fn);
				translate([0,0,stretch*egg_radius])cube(2*stretch*egg_radius, center = true);
				//translate([0,-40,0])cube(90, center = true);
			}
			sphere(r=egg_radius, $fn=fn);
			
		}
	}
//translate([0,0,5])cube(40, center = true);
}
//This cuts out the opening for our circuit board
//translate([0,-8,26])#cube([34.5,47.5,cutout], center = true);
//Light Pipe
//translate([9,-11,-15])#cylinder(h = 70,r=3.1,$fn=fn);

//This cuts out the opening for our circuit board
translate([-18,-42,16])#sensor_cutout();
//This cuts out the opening for the switch
translate([26.5,-10,18.5])#switch_cutout();
}

//standoff(Shape,BaseHeight,BaseDia,Style,TopHeight,TopDia);

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

//Modules

//Egg Modules
module sensor_cutout(){
    //Below defines the dimensions for the sensor module
    xdim = 37;
    ydim = 65;
    zdim = 15;
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

// Parameters: style, height, diameter, Thread_Height
module standoffTop(style, baseHeight, topHeight, diameter) {
	radius = diameter/2;
	if (style == 1) { //male
		translate([0,0, baseHeight + topHeight/2 - 0.1])
			cylinder(topHeight + 0.1, r = radius, $fn = RndFrags, center = true);
	} else if (style == 2) { // snapin
		// FIX: large top height - this is above base
		notchW = radius/1.5;//width of the flexy notch in terms of peg radius
		translate([0,0, baseHeight - 0.1]) // -2 needs to be a calc
			difference() {
				union() {
					// top standoff
					cylinder(r= radius,h = topHeight+1, $fn = RndFrags); //master peg
					// underside slant - relief for overhang
					translate([0,0,topHeight])
						cylinder(r1=radius,r2= radius+.5, h =1, $fn = RndFrags);
					// top slant - insertion cone
					translate([0,0,topHeight+1])
						cylinder(r1=radius+.5,r2= radius-.25, h =1, $fn = RndFrags);
					} //union
				// Internal cylinder cutout
				cylinder(r= radius-.5, h = topHeight+3, $fn = RndFrags);
				//notch for insertion flex
				translate([-(diameter+2)/2,-notchW/2,-0.1])
					cube([diameter+2,notchW,topHeight+2.2]);
			} //difference
	} else if (style == 3) { // flat - No top
	} else if (style == 4) { // female
		translate([0,0, baseHeight - topHeight/2 + 0.1])
			cylinder(topHeight + 0.1, r = radius, $fn = RndFrags, center = true);
	} else if (style == 5) { // hollow
		translate([0,0, baseHeight/2])
			cylinder(baseHeight + 0.1, r = radius, $fn = RndFrags, center = true);
	}
};
// Parameters: shape, height, diameter
module standoffBase(shape, height, diameter) {
	radius = diameter/2;
	if (shape == 1) { // round
		translate([0, 0, height/2])
			cylinder(height, r = radius, center = true, $fn = RndFrags);
	} else if (shape == 2) { // square
		translate([0,0, height/2])
			cube([diameter, diameter, height], center = true);
	} else if (shape == 3) { // hex
		cylinder(h = height, r = radius, center = false, $fn = 6);
	}
};
// Parameters: shape, style, Body_Diameter, Body_Height, Thread_Height, Thread_Dia
module standoff(shape, baseHeight, baseDiameter, style, topHeight, topDiameter) {
	if (style == 1 || style == 2) { // male or snap-in
		union() {
			standoffBase(shape, baseHeight, baseDiameter);
			standoffTop(style, baseHeight, topHeight, topDiameter);
		}
	} else if (style == 4 || style == 5) { // female or hollow
		difference() {
			standoffBase(shape, baseHeight, baseDiameter);
			standoffTop(style, baseHeight, topHeight, topDiameter);
		}
	} else if (style==3) { // flat - no top
		standoffBase(shape, baseHeight, baseDiameter);
	}
};

//function range2vector(r) = [ for (i=r) i];

//ShapesV = range2vector(Shapes);
//StylesV = range2vector(Styles);
//if (Generate == 1) { // single
//	standoff(Shape,BaseHeight,BaseDia,Style,TopHeight,TopDia);
//} else if (Generate == 2) { // array all same
//    rotate([0,0,90])
//    translate([-10,0,-25])
//	translate([-(X_Offset * (Rows+1))/2, -(Y_Offset * (Columns+1))/2, 0])
//		union(){
//			for (j = [1 : Rows]){
//				translate([0,j * Y_Offset,0])
//					for( i = [1 : Columns]){
//						translate([i * X_Offset,0,0])
//							standoff(Shape,BaseHeight,BaseDia,Style,TopHeight,TopDia);
//					} // for
//			} // for
//		}; // union
//};