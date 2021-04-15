// Berserk is a UCI compliant chess engine written in C
// Copyright (C) 2021 Jay Honnold

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifdef TUNE
#ifndef TEXEL_H
#define TEXEL_H

#include <stdio.h>
#include <stdlib.h>

#include "types.h"

typedef struct {
  double result;
  char fen[128];
} Position;

typedef struct {
  Position* positions;
  int n;
  int threadid;
  double error;
} BatchJob;

typedef double TexelGradient[2];

typedef struct {
  int idx;
  int count;
  Score min;
  Score max;
  char* name;
  TScore* vals;
  TexelGradient* gradients;
} TexelParam;

void Texel();
void SGD(TexelParam* params, int numParams, Position* positions, int numPositions);

void CalculateSingleGradient(TexelParam param, Position* positions, int numPositions, double base);
void CalculateGradients(TexelParam* params, int numParams, Position* positions, int numPositions, double base);
Position* LoadPositions();

void PrintParams(TexelParam* params, int numParams, double best, double current, int epoch);

void determineK(Position* positions, int n);
double totalError(Position* positions, int n);
void* batchError(void* arg);
double error(Position* p);
double sigmoid(Score score);

double scaleDown(Score val, Score min, Score max);
Score scaleUp(Score val, Score min, Score max);

void addParamBounded(char* name, int count, TScore* score, Score min, Score max, TexelParam* params, int* n);
void addParams(TexelParam* params, int* numParams);

void shufflePositions(Position* positions, int n);
#endif
#endif