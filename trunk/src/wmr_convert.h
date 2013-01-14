/**
 * Oregon Scientific WMR100/200/WMRS200/I300/I600/RMS600 protocol. Tested on wmrs200.
 *
 * Copyright:
 * 2009 Barnaby Gray <barnaby@pickle.me.uk>
 * 2012-2013 Den68 <idg68@yandex.ru> 
 * Latest download URL: http://www.nkl.ru/support/wmr/
 * Global download URL: http://code.google.com/p/wmr/
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _WMR_LOGGER_CONVERT_H
#define _WMR_LOGGER_CONVERT_H

// Conversion parameters for english units
// Second and optional third factor is for adapting to actual stored values

// #define WMR_SCALE_DEFAULT	1.0	// No scaling
// #define WMR_SCALE_MS_TO_MPH	2.2369362920544   * 0.1
// #define WMR_SCALE_C_TO_F	9 / 5 +  32
// #define WMR_SCALE_CM_TO_IN	0.3937007874      * 0.1 * 0.3
// #define WMR_SCALE_HPA_TO_INHG	0.029530058646697 * 0.1
// #define WMR_SCALE_HPA_TO_MM	0.75  // 0.75006375541921
// #define WMR_SCALE_HPA_TO_PSI	0.0145  // 0.014503773773022 
// #define WMR_SCALE_HPA_TO_BAR	0.001
// #define WMR_SCALE_HPA_TO_MBAR	1.0

#define cnv_def_psi( i ) 	(i) = (i) * 0.0145  // 0.014503773773022 
#define cnv_def_bar( i ) 	(i) = (i) *  0.001
#define cnv_def_mbar( i ) 	(i) = (i) *  1.0
#define cnv_def_mpa( i ) 	(i) = (i) *  0.0001 
#define cnv_def_mmhg( i ) 	(i) = (i) * 0.75  // 0.75006375541921
#define cnv_def_inhg( i ) 	(i) = (i) *  0.02953 

#define cnv_c_f( i )	 	(i) = ( ( (i) *  1.8 ) +32 )
#define cnv_f_c( i )	 	(i) = ( ( ( (i) - 32 ) * 5) / 9 )

#define cnv_mm_inch( i )	(i) = ( (i) * 0.03937 ) 
#define cnv_cm_inch( i )	(i) = ( (i) * 0.3937 ) 
#define cnv_ms_mph( i )		(i) = ( (i) * 0.44704 )
#define cnv_ms_mps( i )		(i) = ( (i) * 1609.344 )
 


#define WMR_SCALE_OFFS_TO_DEGREE	22.5
#define WMR_OFFSET_DEFAULT		0.0	// No offset
#define WMR_OFFSET_C_TO_F		32.0


#endif
