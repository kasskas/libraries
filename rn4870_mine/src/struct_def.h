/*
 * IncFile1.h
 *
 * Created: 21-Dec-17 12:50:35
 *  Author: as
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

	typedef struct  {
		long unsigned int	end_UUID;
		char				nr_bytes;
		unsigned int		handle;
		unsigned int		properies;
		unsigned long int		data_to_send;
		unsigned long int		data_to_send_2;
	}BLE_char;



#endif /* INCFILE1_H_ */