// IntToBMP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdint>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <memory>

#pragma pack( push, 1 ) 
struct BMP
{
    BMP();
    struct
    {
        uint16_t ID;
        uint32_t fileSizeInBytes;
        uint16_t reserved1;
        uint16_t reserved2;
        uint32_t pixelArrayOffsetInBytes;
    } FileHeader;

    enum class CompressionMethod : uint32_t {   BI_RGB              = 0x00, 
                                                BI_RLE8             = 0x01,
                                                BI_RLE4             = 0x02,
                                                BI_BITFIELDS        = 0x03,
                                                BI_JPEG             = 0x04,
                                                BI_PNG              = 0x05,
                                                BI_ALPHABITFIELDS   = 0x06 };

    struct
    {
        uint32_t headerSizeInBytes;
        uint32_t bitmapWidthInPixels;
        uint32_t bitmapHeightInPixels;
        uint16_t colorPlaneCount;
        uint16_t bitsPerPixel;
        CompressionMethod compressionMethod;
        uint32_t bitmapSizeInBytes;
        int32_t horizontalResolutionInPixelsPerMeter;
        int32_t verticalResolutionInPixelsPerMeter;
        uint32_t paletteColorCount;
        uint32_t importantColorCount;
    } DIBHeader;
};
#pragma pack( pop )

BMP::BMP()
{
    //Initialized fields
    FileHeader.ID                                   = 0x4d42; // == 'BM' (little-endian)
    FileHeader.reserved1                            = 0;
    FileHeader.reserved2                            = 0;
    FileHeader.pixelArrayOffsetInBytes              = sizeof( FileHeader ) + sizeof( DIBHeader );
    DIBHeader.headerSizeInBytes                     = 40;
    DIBHeader.colorPlaneCount                       = 1;
    DIBHeader.bitsPerPixel                          = 32;
    DIBHeader.compressionMethod                     = CompressionMethod::BI_RGB;
    DIBHeader.horizontalResolutionInPixelsPerMeter  = 2835; // == 72 ppi
    DIBHeader.verticalResolutionInPixelsPerMeter    = 2835; // == 72 ppi
    DIBHeader.paletteColorCount                     = 0;
    DIBHeader.importantColorCount                   = 0;
}

void Exit( void )
{
    std::cout << "Press a key to exit...";
    std::getchar();

    exit( 0 );
}

void MakeIntegerFile( const std::string& integerFilename )
{
    const uint32_t intCount = 1 << 20; //Generate 1M (2^20) integers
    std::unique_ptr< int32_t[] > buffer( new int32_t[ intCount ] ); 

    std::mt19937 rng;
    uint32_t rngSeed = static_cast< uint32_t >( time( NULL ) );
    rng.seed( rngSeed );

    std::uniform_int_distribution< int32_t > dist( INT32_MIN, INT32_MAX );

    for( size_t i = 0; i < intCount; ++i )
    {
        buffer[ i ] = dist( rng );
    }

    std::ofstream writeFile( integerFilename, std::ofstream::binary );

    if( !writeFile )
    {
        std::cout << "Error writing " << integerFilename << ".\n";
        Exit();
    }

    writeFile << buffer[ 0 ];
    for( size_t i = 1; i < intCount; ++i )
    {
        writeFile << " " << buffer[ i ];
    }
}

int _tmain(int argc, _TCHAR* argv[])  //Replace with int main( int argc, char* argv[] ) if you're not under Visual Studio
{
    //Assumption: 32-bit signed integers
    //Assumption: Distribution of values range from INT32_MIN through INT32_MAX, inclusive
    //Assumption: number of integers contained in file are unknown
    //Assumption: source file of integers is a series of space-delimitied strings representing integers
    //Assumption: source file's contents are valid
    //Assumption: non-rectangular numbers of integers yield non-rectangular bitmaps (final scanline may be short)
    //            This may cause some .bmp parsers to fail; others may pad with 0's.  For simplicity, this implementation
    //            attempts to render square bitmaps.

    const std::string integerFilename = "integers.txt";
    const std::string bitmapFilename = "bitmap.bmp";

    std::cout << "Creating file of random integers...\n";
    MakeIntegerFile( integerFilename );

    std::vector< int32_t >integers; //If quantity of integers being read is known, reserve or resize vector or use array

    //Read integers from file
    std::cout << "Reading integers from file...\n";
    {   //Nested scope will release ifstream resource when no longer needed
        std::ifstream readFile( integerFilename );

        if( !readFile )
        {
            std::cout << "Error reading " << integerFilename << ".\n";
            Exit();
        }

        std::string number;
        while( readFile.good() )
        {
            std::getline( readFile, number, ' ' );
            integers.push_back( std::stoi( number ) );
        }

        if( integers.size() == 0 )
        {
            std::cout << "No integers read from " << integerFilename << ".\n";
            Exit();
        }
    }

    //Construct .bmp
    std::cout << "Constructing .BMP...\n";
    BMP bmp;
    size_t intCount = integers.size();
    bmp.DIBHeader.bitmapSizeInBytes = intCount * sizeof( integers[ 0 ] );
    bmp.FileHeader.fileSizeInBytes = bmp.FileHeader.pixelArrayOffsetInBytes + bmp.DIBHeader.bitmapSizeInBytes;
    bmp.DIBHeader.bitmapWidthInPixels = static_cast< uint32_t >( ceil( sqrt( intCount ) ) );
    bmp.DIBHeader.bitmapHeightInPixels = static_cast< uint32_t >( ceil( intCount / static_cast< float >( bmp.DIBHeader.bitmapWidthInPixels ) ) );

    //Write integers to .bmp file
    std::cout << "Writing .BMP...\n";
    {
        std::ofstream writeFile( bitmapFilename, std::ofstream::binary );

        if( !writeFile )
        {
            std::cout << "Error writing " << bitmapFilename << ".\n";
            Exit();
        }

        writeFile.write( reinterpret_cast< char * >( &bmp ), sizeof( bmp ) );
        writeFile.write( reinterpret_cast< char * >( &integers[ 0 ] ), bmp.DIBHeader.bitmapSizeInBytes );
    }

    //Exit
    Exit();
} 