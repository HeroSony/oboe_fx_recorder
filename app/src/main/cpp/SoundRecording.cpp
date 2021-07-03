#include "SoundRecording.h"


int32_t SoundRecording::write(const float *sourceData, int32_t numSamples) {

    // Check that data will fit, if it doesn't then create new array,
    // copy over old data to new array then delete old array and
    // point mData to new array.
    if (mWriteIndex + numSamples > (kMaxSamples * mIteration)) {

        LOGW(TAG, "write(): mWriteIndex + numSamples > kMaxSamples");
        mIteration++;

        int32_t newSize = kMaxSamples * mIteration;

        auto * newData = new float[newSize] { 0 };
        std::copy(mData, mData + mTotalSamples, newData);

        delete[] mData;
        mData = newData;

    }

    for (int i = 0; i < numSamples; ++i) {
        mData[mWriteIndex++] = sourceData[i] * gain_factor;
    }

    mTotalSamples += numSamples;

    return numSamples;
}

int32_t SoundRecording::read(float *targetData, int32_t numSamples) {

    LOGD(TAG, "read(): ");

    int32_t framesRead = 0;

    while (framesRead < numSamples && mReadIndex < mTotalSamples) {
        targetData[framesRead++] = mData[mReadIndex++];
        if (mIsLooping && mReadIndex == mTotalSamples) mReadIndex = 0;
    }

    return framesRead;
}

SndfileHandle SoundRecording::createFile(const char *outfilename, int32_t outputChannels, int32_t sampleRate) {

    LOGD(TAG, "createFile(): ");

    SndfileHandle file;
    int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    LOGD(TAG, "createFile(): Creating file ");

    file = SndfileHandle (outfilename, SFM_WRITE, format, outputChannels, sampleRate);

    return file;
}

void SoundRecording::writeFile(SndfileHandle sndfileHandle) {

    LOGD(TAG, "writeFile(): ");

    int32_t framesRead = 0, bufferLength = mTotalSamples;
    sf_count_t framesWrite = 0;

    auto *buffer = new float[bufferLength];

    fillArrayWithZeros(buffer, bufferLength);

    while ((framesRead = read(buffer, bufferLength)) > 0) {
        framesWrite = sndfileHandle.write(buffer, framesRead);
        LOGD("framesWrite: ");
    }

}

void SoundRecording::readFileInfo(const char * fileName) {

    LOGD(TAG, "readFileInfo(): ");

    SndfileHandle file;
    file = SndfileHandle(fileName) ;

    LOGD (TAG, "readFileInfo(): Opened file => ") ;
    LOGD(TAG, fileName);

    LOGI (TAG, "readFileInfo(): Sample rate : ", file.samplerate());
    LOGI(TAG, std::to_string(file.samplerate()).c_str());
    LOGI (TAG, "readFileInfo(): Channels : ", file.channels()) ;
    LOGI(TAG, std::to_string(file.channels()).c_str());
    LOGI (TAG, "readFileInfo(): Frames : ", file.frames()) ;
    LOGI(TAG, std::to_string(file.frames()).c_str());

}

void SoundRecording::initiateWritingToFile(const char *outfilename, int32_t outputChannels, int32_t sampleRate) {

    LOGD(TAG, "initiateWritingToFile(): ");

    SndfileHandle handle = createFile(outfilename, outputChannels, sampleRate);
    writeFile(handle);
    readFileInfo(outfilename);

}
