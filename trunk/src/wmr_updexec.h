/*
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

#ifndef _WMR_LOGGER_UPDEXEC_H
#define _WMR_LOGGER_UPDEXEC_H

#define WMR_EXEC_FOUND      0
#define WMR_EXEC_NOT_FOUND  1
#define WMR_EXEC_READ_ERROR 2
#define WMR_EXEC_OPEN_ERROR 3
#define WMR_EXEC_NOARG      4

#define WMR_TMPL_UPD_NSENS_TEMP	\
				"temp_%d_humidity=\"%d\" " \
				"temp_%d_smiley=\"%d\" " \
				"temp_%d_temp=\"%.1f\" " \
				"temp_%d_dewpoint=\"%.1f\" " \
				"temp_%d_trendTxt=\"%s\" " \
				"temp_%d_smileyTxt=\"%s\" "

#define WMR_TMPL_UPD_NSENS_WATER \
				"water_%d_temp=\"%.1f\" "

#define WMR_TMPL_UPD_NSENS_OTHER \
				"uv=\"%d\" " \
				"pressure=\"%d\" " \
				"forecast=\"%d\" " \
				"rain_rate=\"%d\" " \
				"rain_hour=\"%.1f\" " \
				"rain_day=\"%.1f\" " \
				"rain_total=\"%.1f\" " \
				"wind_dir=\"%d\" " \
				"wind_lowsp=\"%d\" " \
				"wind_hisp=\"%d\" " \
				"wind_cursp=\"%.1f\" " \
				"wind_avgsp=\"%.1f\" " \
				"wind_chill=\"%.1f\"" 

#define WMR_TMPL_UPD_EXEC_DEBUG \
				"shmID: %d PROCESS: %s\n" \
				"temp_0_humidity=\"%d\" \n" \
				"temp_0_temp=\"%.1f\" \n" \
				"temp_0_dewpoint=\"%.1f\" \n" \
				"temp_0_smiley=\"%d\" \n" \
				"temp_0_trendTxt=\"%s\" \n" \
				"temp_0_smileyTxt=\"%s\" \n" \
				"temp_1_humidity=\"%d\" \n" \
				"temp_1_temp=\"%.1f\" \n" \
				"temp_1_dewpoint=\"%.1f\" \n" \
				"temp_1_smiley=\"%d\" \n" \
				"temp_1_trendTxt=\"%s\" \n" \
				"temp_1_smileyTxt=\"%s\" \n" \
				"water_0_temp=\"%.1f\" \n" \
				"uv=\"%d\" \n" \
				"pressure=\"%d\" \n" \
				"forecast=\"%d\" \n" \
				"rain_rate=\"%d\" \n" \
				"rain_hour=\"%.1f\" \n" \
				"rain_day=\"%.1f\" \n" \
				"rain_total=\"%.1f\" \n" \
				"wind_dir=\"%d\" \n" \
				"wind_lowsp=\"%d\" \n" \
				"wind_hisp=\"%d\" \n" \
				"wind_cursp=\"%.1f\" \n" \
				"wind_avgsp=\"%.1f\" \n" \
				"wind_chill=\"%.1f\"\n" 

#endif
