/*
	JUCI Backend Websocket API Server

	Copyright (C) 2016 Martin K. Schröder <mkschreder.uk@gmail.com>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version. (Please read LICENSE file on special
	permission to include this software in signed images). 

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
*/
#pragma once

#include "orange_server.h"
#include <pthread.h>
#include <semaphore.h>

struct orange; 

struct orange_rpc{
	//struct blob buf; 
	//struct blob out; 
	orange_server_t server; 
	struct orange *ctx; 
	unsigned long long timeout_us; 
	pthread_t *threads; 
	pthread_t monitor; 
	pthread_t eq_task; 
	pthread_mutex_t lock; 
	unsigned int num_workers; 
	int shutdown; 
	struct avl_tree requests; 

	// number of busy workers 
	sem_t sem_bw; 
}; 

void orange_rpc_init(struct orange_rpc *self, orange_server_t server, struct orange *ctx, unsigned long long timeout_us, unsigned int num_workers); 
void orange_rpc_deinit(struct orange_rpc *self); 

void orange_rpc_broadcast_event(struct orange_rpc *self, const char *name, const struct blob_field *data); 

#ifndef CONFIG_THREADS
int orange_rpc_process_requests(struct orange_rpc *self); 
#endif
