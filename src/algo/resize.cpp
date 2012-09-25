#include "Image.h"

void Image::resizeImage(const int rate) {
	float r = rate / 100.;
	float w = tempImg->width() * r;
	float h = tempImg->height() * r;
	float x, y;
	float ax, ay, bx, by, cx, cy, dx, dy;
	float ar, ag, ab, br, bg, bb, cr, cg, cb, dr, dg, db;
	float er, eg, eb, fr, fg, fb;
	QRgb rgb;

	QImage* newImage = new QImage(w, h, tempImg->format());
	for (int i = 0; i < (int)w; ++i)
		for (int j = 0; j < (int)h; ++j) {
			x = (float)i / r;
			y = (float)j / r;

			// to avoid that x and y excceed the range of the 
			// two-dimension vector.
			if ((float)tempImg->width() - x < 2)
				x = tempImg->width() - 2;
			if ((float)tempImg->height() - y < 2)
				y = tempImg->height() - 2;

			ax = x, ay = y;
			bx = x + 1; by = y;
			cx = x, cy = y + 1;
			dx = x + 1, dy = y + 1;
			
			rgb = tempImg->pixel(ax, ay);
			ar = qRed(rgb);	
			ag = qGreen(rgb);	
			ab = qBlue(rgb);	
	
			rgb = tempImg->pixel(bx, by);
			br = qRed(rgb);	  	
			bg = qGreen(rgb);	 	
			bb = qBlue(rgb);	 	

			rgb = tempImg->pixel(cx, cy);
			cr = qRed(rgb);	  	
			cg = qGreen(rgb);	 	
			cb = qBlue(rgb);	 	
	
			rgb = tempImg->pixel(dx, dy);
			dr = qRed(rgb);	  	
			dg = qGreen(rgb);	 	
			db = qBlue(rgb);	 	

			er = ar + (br - ar) * (x - ax);
			fr = cr + (dr - cr) * (x - cx);
			int R = (int)(er + (fr - er) * (y - ay));

			eg = ag + (bg - ag) * (x - ax);
			fg = cg + (dg - cg) * (x - cx);
			int G = (int)(eg + (fg - eg) * (y - ay));

			eb = ab + (bb - ab) * (x - ax);
			fb = cb + (db - cb) * (x - cx);
			int B = (int)(eb + (fb - eb) * (y - ay));

			newImage->setPixel(i, j, qRgb(R, G, B));
		}
	img = newImage;
	getHistogram();
	update();
}
