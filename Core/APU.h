#pragma once

#include "stdafx.h"
#include "IMemoryHandler.h"
#include "IAudioDevice.h"
#include "Snapshotable.h"

class MemoryManager;
class SquareChannel;
class TriangleChannel;
class NoiseChannel;
class DeltaModulationChannel;
class ApuFrameCounter;
class SoundMixer;
enum class FrameType;
enum class NesModel;

class APU : public Snapshotable, public IMemoryHandler
{
	private:
		static APU* Instance;

		uint32_t _previousCycle;
		uint32_t _currentCycle;

		vector<unique_ptr<SquareChannel>> _squareChannel;
		unique_ptr<TriangleChannel> _triangleChannel;
		unique_ptr<NoiseChannel> _noiseChannel;
		unique_ptr<DeltaModulationChannel> _deltaModulationChannel;

		unique_ptr<ApuFrameCounter> _frameCounter;

		MemoryManager* _memoryManager;

		shared_ptr<SoundMixer> _mixer;

		NesModel _nesModel;

	private:
		bool NeedToRun(uint32_t currentCycle);
		void Run();
		void EndFrame();

		static void FrameCounterTick(FrameType type);

	protected:
		void StreamState(bool saving);

	public:
		APU(MemoryManager* memoryManager);
		~APU();

		void Reset(bool softReset);
		void SetNesModel(NesModel model, bool forceInit = false);

		uint8_t ReadRAM(uint16_t addr);
		void WriteRAM(uint16_t addr, uint8_t value);
		void GetMemoryRanges(MemoryRanges &ranges);

		void Exec();
		static void ExecStatic();

		static void StaticRun();
};