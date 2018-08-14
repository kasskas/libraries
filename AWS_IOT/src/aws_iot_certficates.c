/*
 * Copyright 2010-2015 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * Additions Copyright 2016 Espressif Systems (Shanghai) PTE LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

/**
 * @file aws_iot_certifcates.c
 * @brief File to store the AWS certificates in the form of arrays
 */

#ifdef __cplusplus
extern "C" {
#endif

const char aws_root_ca_pem[] = {"-----BEGIN CERTIFICATE-----\n" \
                         "MIIE0zCCA7ugAwIBAgIQGNrRniZ96LtKIVjNzGs7SjANBgkqhkiG9w0BAQUFADCB\n" \
                         "yjELMAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQL\n" \
                         "ExZWZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJp\n" \
                         "U2lnbiwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxW\n" \
                         "ZXJpU2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0\n" \
                         "aG9yaXR5IC0gRzUwHhcNMDYxMTA4MDAwMDAwWhcNMzYwNzE2MjM1OTU5WjCByjEL\n" \
                         "MAkGA1UEBhMCVVMxFzAVBgNVBAoTDlZlcmlTaWduLCBJbmMuMR8wHQYDVQQLExZW\n" \
                         "ZXJpU2lnbiBUcnVzdCBOZXR3b3JrMTowOAYDVQQLEzEoYykgMjAwNiBWZXJpU2ln\n" \
                         "biwgSW5jLiAtIEZvciBhdXRob3JpemVkIHVzZSBvbmx5MUUwQwYDVQQDEzxWZXJp\n" \
                         "U2lnbiBDbGFzcyAzIFB1YmxpYyBQcmltYXJ5IENlcnRpZmljYXRpb24gQXV0aG9y\n" \
                         "aXR5IC0gRzUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCvJAgIKXo1\n" \
                         "nmAMqudLO07cfLw8RRy7K+D+KQL5VwijZIUVJ/XxrcgxiV0i6CqqpkKzj/i5Vbex\n" \
                         "t0uz/o9+B1fs70PbZmIVYc9gDaTY3vjgw2IIPVQT60nKWVSFJuUrjxuf6/WhkcIz\n" \
                         "SdhDY2pSS9KP6HBRTdGJaXvHcPaz3BJ023tdS1bTlr8Vd6Gw9KIl8q8ckmcY5fQG\n" \
                         "BO+QueQA5N06tRn/Arr0PO7gi+s3i+z016zy9vA9r911kTMZHRxAy3QkGSGT2RT+\n" \
                         "rCpSx4/VBEnkjWNHiDxpg8v+R70rfk/Fla4OndTRQ8Bnc+MUCH7lP59zuDMKz10/\n" \
                         "NIeWiu5T6CUVAgMBAAGjgbIwga8wDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8E\n" \
                         "BAMCAQYwbQYIKwYBBQUHAQwEYTBfoV2gWzBZMFcwVRYJaW1hZ2UvZ2lmMCEwHzAH\n" \
                         "BgUrDgMCGgQUj+XTGoasjY5rw8+AatRIGCx7GS4wJRYjaHR0cDovL2xvZ28udmVy\n" \
                         "aXNpZ24uY29tL3ZzbG9nby5naWYwHQYDVR0OBBYEFH/TZafC3ey78DAJ80M5+gKv\n" \
                         "MzEzMA0GCSqGSIb3DQEBBQUAA4IBAQCTJEowX2LP2BqYLz3q3JktvXf2pXkiOOzE\n" \
                         "p6B4Eq1iDkVwZMXnl2YtmAl+X6/WzChl8gGqCBpH3vn5fJJaCGkgDdk+bW48DW7Y\n" \
                         "5gaRQBi5+MHt39tBquCWIMnNZBU4gcmU7qKEKQsTb47bDN0lAtukixlE0kF6BWlK\n" \
                         "WE9gyn6CagsCqiUXObXbf+eEZSqVir2G3l6BFoMtEMze/aiCKm0oHw0LxOXnGiYZ\n" \
                         "4fQRbxC1lfznQgUy286dUV4otp6F01vvpX1FQHKOtw5rDgb7MzVIcbidJ4vEZV8N\n" \
                         "hnacRHr2lVz2XTIIM6RUthg/aFzyQkqFOFSDX9HoLPKsEdao7WNq\n" \
"-----END CERTIFICATE-----\n"};

const char certificate_pem_crt[] = {"-----BEGIN CERTIFICATE-----\n" \
                              "MIIDWjCCAkKgAwIBAgIVAJ94YiFjNBlhIuveegut6kNxVbjmMA0GCSqGSIb3DQEB\n" \
                              "CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t\n" \
                              "IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0xODA1MDkxNTMz\n" \
                              "NDNaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh\n" \
                              "dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCfBIW7U9m79atkfZfn\n" \
                              "cN1fttKkS1EzOsJKQlXxT85R01kwWwINlTjv6FtMLQaoBE3wsig1c5phLiy6S06u\n" \
                              "y2IvrcZrq9gcLL23HBZiABf3KJLU3vPDvTQiMEBpnZLmJQE1RavXCfHAfQGz5ujC\n" \
                              "pyJXJVjgUe8+3ZGP2lZs3BeNX11w1VH5wCZpenMmFJqZS6TOnTV8xOzwGdRkWTj1\n" \
                              "zgpU69Sf1ChjPzft1gKEw2UL6zQ5zHnrfBKFLeXYt2E7BUYCHrOqAMSrF8mNrpfl\n" \
                              "BJPlOlOv0b9ldKFtGvaQ0OgjpHmoRV9rThvzmMd3198i+xEo1A+Axt3oMiltpJ2U\n" \
                              "IlT3AgMBAAGjYDBeMB8GA1UdIwQYMBaAFItouOMNGSkZDjzHnee6tkqwbWOUMB0G\n" \
                              "A1UdDgQWBBRLODpr32PB69Yrc6ywYaOeZwpFWzAMBgNVHRMBAf8EAjAAMA4GA1Ud\n" \
                              "DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEAoiiFgpxkCrwXLm88XoOIkP7r\n" \
                              "hjrsruqUOAnIyxLSXhI90KGT76PKGMA3ZAbf0FdhnYNJENtzTDfUsNVgGN4fgWHb\n" \
                              "g8EcSckhYYNdEsABZFKb8OZcYWFHD71OfPcQAHSg5HWGv7ymR3bN9mqLeeluBOwC\n" \
                              "ff21fWsf9pJRHIzNQ5xWOm4YOkUSOA3b1DUmSV/5RIxq8Zh5YxeD40BU0wHHbXbE\n" \
                              "cgXZqjSM0/OWOhpHj0fMq30H+ZoD2iNB3ed6JjPCF3TvDHn4Lka/0VD3PC3dZakA\n" \
                              "BOuod4AoWaheIHQtGbpQnzs56v7AcEc1ecxM9HQQJYZX2wm8uV6WHztsWSqBCA==\n" \
                              "-----END CERTIFICATE-----\n"};

const char private_pem_key[] = {"-----BEGIN RSA PRIVATE KEY-----\n" \
                             "MIIEowIBAAKCAQEAnwSFu1PZu/WrZH2X53DdX7bSpEtRMzrCSkJV8U/OUdNZMFsC\n" \
                             "DZU47+hbTC0GqARN8LIoNXOaYS4suktOrstiL63Ga6vYHCy9txwWYgAX9yiS1N7z\n" \
                             "w700IjBAaZ2S5iUBNUWr1wnxwH0Bs+bowqciVyVY4FHvPt2Rj9pWbNwXjV9dcNVR\n" \
                             "+cAmaXpzJhSamUukzp01fMTs8BnUZFk49c4KVOvUn9QoYz837dYChMNlC+s0Ocx5\n" \
                             "63wShS3l2LdhOwVGAh6zqgDEqxfJja6X5QST5TpTr9G/ZXShbRr2kNDoI6R5qEVf\n" \
                             "a04b85jHd9ffIvsRKNQPgMbd6DIpbaSdlCJU9wIDAQABAoIBABhFZXARPVOODMn6\n" \
                             "zXu6418flYkUIeGy30LcWyfI6ZHds2hJC8gs9ZLQoVbALJrqhUbuumpmKbMZjCQn\n" \
                             "KGxPiL4ERRvcD9FFFvPi6pusrfvAiqDJIuXGdDWfrcUxEuHj1gpehvr8fpTFv8PI\n" \
                             "w9AqGHi6r5UVjHHI+dW+GqDk+wdNwGraSHjdrCK/kRpPbs8h/NETEzM/C4Ep+n9J\n" \
                             "o7DXyLaAE0jNB5r9OmqduGtfGderLE/7Pj9W6QdRwMd0zeujC6k9jaLPi2KBXENR\n" \
                             "qwfU2wq3/KOxCZFAre1IrhMviBsFLWQ/UKis5Mm/IW4f4r7FQ9hMEyDRAenZHU6P\n" \
                             "D8iamnkCgYEAygv8j26IRaUYBXGD0Xa0Mr3q4/szpqo8RStGc4pGD2eLyA9kkoFX\n" \
                             "wLm06PEZygS8AIHoTQ4BWJAjczTEYKzG5hOza1tLbtaiKuf0cqDStLrDBg8MSAi8\n" \
                             "tlZL/di/XPF3MGm+e3wl3K5ReYiGXlkw0VJVMTLlNjN1XccXyZY//EUCgYEAyXsK\n" \
                             "/UY+Rqo8m118nao145DJ9Wqugd9A5FYQ4L2ETmbxs1Oyf76d2guP3NF68f8l4wwg\n" \
                             "hB68XHz3m/4E7siEq1GpHd22r8kg6kFbFjSPkYeYg02n3/nmcMjJnROLqbAcBr6Z\n" \
                             "MPejxPlfsHv9xLGHO6BYIuT5nc4zfR25YCTTZgsCgYB4HIgX/G2meW6+Ta0/aIHX\n" \
                             "aG+q+DrMaYdK118acKkVn0jJtdzj+2Bfgga6NBpQrl/VLWUb6aeDLqzkYAoeLphP\n" \
                             "Tobq22sMiSv+tcXsHw8jwaMOhwOWDxugiczDK4cXibSBY1uJrVQUzMxCo5a9n+gV\n" \
                             "iAx9IvSANDcheKn7fQaswQKBgHvMk/MOT0PCZJ0ec2y5YoViuQWIOJPqZwgmbhZ5\n" \
                             "vKskDA2hNwPRT1LkWdBYExBRM6lwESa9cAXwb4C1M7i5EvPlqGGGkzMuBYCLCfn5\n" \
                             "7+F/DNJZS/aOqe7RITjYArAQWxg10xFIiKOGiyp49XP/lVWo7575TPuO8QpG0lnm\n" \
                             "JtMDAoGBAMm66IcS6qRWyhnOXU0Ey29fUDNyz8O6IsUlZgk3hzc9NsR7b4XWYeWD\n" \
                             "DCVK7CgYJuxjZJf8K1gWLkPGdAj5wkSDYwjPC3rTCbvvavHstlzC5bxzruo4bMxH\n" \
                             "YtMA5dA16zu8TPpxyLsdhRjCa4KGu18FmG/LBoVsHhqPns6E8K7V\n" \
                             "-----END RSA PRIVATE KEY-----\n"};


#ifdef __cplusplus
}
#endif
