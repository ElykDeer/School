x47d4f0:
 sub esp, 0x18
 mov eax, edx
 mov ecx, dword [eax]
 mov dword [esp+0x8], ecx
 mov ecx, dword [eax+0x4]
 push ebx
 mov dword [esp+0x10], ecx
 mov ecx, dword [eax+0x8]
 mov eax, dword [eax+0xc]
 push ebp
 push esi
 mov dword [esp+0x20], eax
 push edi
 mov dword [esp+0x20], ecx
 xor eax, eax
 mov esi, 0x2
 jmp .x47d520

 .x47d520:
 lea edi, [esi-0x2]
 mov ebx, edi
 and ebx, 0x1f
 mov dword [esp+0x10], ebx
 shr edi, 0x5
 mov ebx, 0x3
 sub ebx, edi
 mov dword [esp+0x14], ebx
 mov edi, eax
 shr edi, 0x5
 shl edi, 0x2
 mov ecx, eax
 and ecx, 0x1f
 lea ebx, [esp+0x24]
 sub ebx, edi
 mov ebx, dword [ebx]
 mov edi, 0x1
 shl edi, cl
 add eax, 0xb
 and ebx, edi
 shr ebx, cl
 mov ecx, dword [esp+0x10]
 mov edi, 0x1
 shl edi, cl
 and ebx, 0x1
 shl ebx, cl
 mov ecx, dword [esp+0x14]
 mov ebp, dword [edx+ecx*4]
 not edi
 and edi, ebp
 or ebx, edi
 cmp eax, 0x78
 mov dword [edx+ecx*4], ebx
 jb .x47d58a

 .x47d58a:
 lea edi, [esi-0x1]
 mov ebx, edi
 and ebx, 0x1f
 mov dword [esp+0x10], ebx
 shr edi, 0x5
 mov ebx, 0x3
 sub ebx, edi
 mov dword [esp+0x14], ebx
 mov edi, eax
 shr edi, 0x5
 shl edi, 0x2
 mov ecx, eax
 and ecx, 0x1f
 lea ebx, [esp+0x24]
 sub ebx, edi
 mov ebx, dword [ebx]
 mov edi, 0x1
 shl edi, cl
 add eax, 0xb
 and ebx, edi
 shr ebx, cl
 mov ecx, dword [esp+0x10]
 mov edi, 0x1
 shl edi, cl
 and ebx, 0x1
 shl ebx, cl
 mov ecx, dword [esp+0x14]
 mov ebp, dword [edx+ecx*4]
 not edi
 and edi, ebp
 or ebx, edi
 cmp eax, 0x78
 mov dword [edx+ecx*4], ebx
 jb .x47d5f4

 .x47d582:
 sub eax, 0x78
 jns .x47d58a

 .x47d5f4:
 mov edi, esi
 and edi, 0x1f
 mov dword [esp+0x10], edi
 mov ebx, esi
 shr ebx, 0x5
 mov edi, 0x3
 sub edi, ebx
 mov dword [esp+0x14], edi
 mov edi, eax
 shr edi, 0x5
 shl edi, 0x2
 mov ecx, eax
 and ecx, 0x1f
 lea ebx, [esp+0x24]
 sub ebx, edi
 mov ebx, dword [ebx]
 mov edi, 0x1
 shl edi, cl
 add eax, 0xb
 and ebx, edi
 shr ebx, cl
 mov ecx, dword [esp+0x10]
 mov edi, 0x1
 shl edi, cl
 and ebx, 0x1
 shl ebx, cl
 mov ecx, dword [esp+0x14]
 mov ebp, dword [edx+ecx*4]
 not edi
 and edi, ebp
 or ebx, edi
 cmp eax, 0x78
 mov dword [edx+ecx*4], ebx
 jb .x47d65d

 .x47d5ec:
 sub eax, 0x78
 jns .x47d5f4

 .x47d587:
 add eax, 0xb

 .x47d65d:
 lea edi, [esi+0x1]
 mov ebx, edi
 and ebx, 0x1f
 mov dword [esp+0x10], ebx
 shr edi, 0x5
 mov ebx, 0x3
 sub ebx, edi
 mov dword [esp+0x14], ebx
 mov edi, eax
 shr edi, 0x5
 shl edi, 0x2
 mov ecx, eax
 and ecx, 0x1f
 lea ebx, [esp+0x24]
 sub ebx, edi
 mov ebx, dword [ebx]
 mov edi, 0x1
 shl edi, cl
 add eax, 0xb
 and ebx, edi
 shr ebx, cl
 mov ecx, dword [esp+0x10]
 mov edi, 0x1
 shl edi, cl
 and ebx, 0x1
 shl ebx, cl
 mov ecx, dword [esp+0x14]
 mov ebp, dword [edx+ecx*4]
 not edi
 and edi, ebp
 or ebx, edi
 cmp eax, 0x78
 mov dword [edx+ecx*4], ebx
 jb .x47d6c7

 .x47d655:
 sub eax, 0x78
 jns .x47d65d

 .x47d5f1:
 add eax, 0xb

 .x47d6c7:
 lea edi, [esi+0x2]
 mov ebx, edi
 and ebx, 0x1f
 mov dword [esp+0x10], ebx
 shr edi, 0x5
 mov ebx, 0x3
 sub ebx, edi
 mov dword [esp+0x14], ebx
 mov edi, eax
 shr edi, 0x5
 shl edi, 0x2
 mov ecx, eax
 and ecx, 0x1f
 lea ebx, [esp+0x24]
 sub ebx, edi
 mov ebx, dword [ebx]
 mov edi, 0x1
 shl edi, cl
 add eax, 0xb
 and ebx, edi
 shr ebx, cl
 mov ecx, dword [esp+0x10]
 mov edi, 0x1
 shl edi, cl
 and ebx, 0x1
 shl ebx, cl
 mov ecx, dword [esp+0x14]
 mov ebp, dword [edx+ecx*4]
 not edi
 and edi, ebp
 or ebx, edi
 cmp eax, 0x78
 mov dword [edx+ecx*4], ebx
 jb .x47d731

 .x47d6bf:
 sub eax, 0x78
 jns .x47d6c7

 .x47d65a:
 add eax, 0xb

 .x47d731:
 lea edi, [esi+0x3]
 mov ebx, edi
 and ebx, 0x1f
 mov dword [esp+0x10], ebx
 shr edi, 0x5
 mov ebx, 0x3
 sub ebx, edi
 mov dword [esp+0x14], ebx
 mov edi, eax
 shr edi, 0x5
 shl edi, 0x2
 mov ecx, eax
 and ecx, 0x1f
 lea ebx, [esp+0x24]
 sub ebx, edi
 mov ebx, dword [ebx]
 mov edi, 0x1
 shl edi, cl
 add eax, 0xb
 and ebx, edi
 shr ebx, cl
 mov ecx, dword [esp+0x10]
 mov edi, 0x1
 shl edi, cl
 and ebx, 0x1
 shl ebx, cl
 mov ecx, dword [esp+0x14]
 mov ebp, dword [edx+ecx*4]
 not edi
 and edi, ebp
 or ebx, edi
 cmp eax, 0x78
 mov dword [edx+ecx*4], ebx
 jb .x47d79b

 .x47d729:
 sub eax, 0x78
 jns .x47d731

 .x47d6c4:
 add eax, 0xb

 .x47d79b:
 add esi, 0x6
 lea ecx, [esi-0x2]
 cmp ecx, 0x78
 jb .x47d520

 .x47d793:
 sub eax, 0x78
 jns .x47d79b

 .x47d72e:
 add eax, 0xb

 .x47d7aa:
 pop edi
 pop esi
 pop ebp
 pop ebx
 add esp, 0x18
 retn 

 .x47d798:
 add eax, 0xb


x47d7c0:
 sub esp, 0xc
 push ebx
 push ebp
 push esi
 mov esi, 0x1d
 push edi
 mov dword [esp+0x10], esi
 mov edi, 0x1d0

 .x47d866:
 lea ebp, [esi-0x1]
 test ebp, ebp
 mov ecx, ebp
 mov dword [esp+0x18], ebp
 mov dword [esp+0x10], ecx
 jl .x47d8c9

 .x47d814:
 mov esi, ebp
 and esi, 0x7
 shl esi, 0x2
 mov edx, ebp
 shr edx, 0x3
 mov ebx, 0x3
 sub ebx, edx
 mov ecx, esi
 mov edx, 0xf
 shl edx, cl
 mov ecx, dword [esp+0x20]
 mov ebx, dword [ecx+ebx*4]
 mov ecx, esi
 mov esi, dword [esp+0x10]
 and ebx, edx
 shr ebx, cl
 movzx eax, al
 movzx ecx, byte [eax+edi+0x51e890]
 movzx edx, bl
 xor edx, ecx
 mov al, byte [edx+edi+0x51e890]
 dec ebp
 cmp ebp, esi
 jg .x47d814

 .x47d8c9:
 movzx ecx, al
 mov esi, 0x3
 sub esi, ebx
 xor ebx, ebx
 mov bl, byte [ecx+edi+0x51e890]
 mov ecx, edx
 mov eax, 0xf
 shl eax, cl
 not eax
 and ebx, 0xf
 shl ebx, cl
 mov ecx, eax
 mov eax, dword [esp+0x20]
 mov edx, dword [eax+esi*4]
 and ecx, edx
 or ebx, ecx
 sub edi, 0x10
 mov dword [eax+esi*4], ebx
 mov esi, ebp
 mov dword [esp+0x10], esi
 jns .x47d7d5

 .x47d877:
 mov esi, ecx
 shr ecx, 0x3
 and esi, 0x7
 shl esi, 0x2
 mov ebx, 0x3
 sub ebx, ecx
 mov ecx, esi
 mov ebp, 0xf
 shl ebp, cl
 mov ecx, dword [esp+0x20]
 mov ebx, dword [ecx+ebx*4]
 mov ecx, esi
 and ebx, ebp
 shr ebx, cl
 movzx eax, al
 movzx eax, byte [eax+edi+0x51e890]
 movzx ecx, bl
 xor ecx, eax
 mov al, byte [ecx+edi+0x51e890]
 mov ecx, dword [esp+0x10]
 dec ecx
 mov dword [esp+0x10], ecx
 jns .x47d877

 .x47d85e:
 mov edx, dword [esp+0x18]
 mov ebx, dword [esp+0x14]

 .x47d7d5:
 mov edx, esi
 and edx, 0x7
 shl edx, 0x2
 mov ebx, esi
 shr ebx, 0x3
 mov ecx, edx
 mov ebp, 0xf
 shl ebp, cl
 mov ecx, dword [esp+0x20]
 mov eax, 0x3
 sub eax, ebx
 mov eax, dword [ecx+eax*4]
 and eax, ebp
 mov ecx, edx
 shr eax, cl
 cmp edi, 0x1d0
 mov dword [esp+0x18], edx
 mov dword [esp+0x14], ebx
 mov ebp, 0x1d
 jge .x47d866

 .x47d90b:
 pop edi
 pop esi
 pop ebp
 pop ebx
 add esp, 0xc
 retn 

 .x47d8c1:
 mov ebx, dword [esp+0x14]
 mov ebp, dword [esp+0x18]


x47d450:
 push ebp
 push esi
 push edi
 push ebx
 mov ebx, edx
 mov eax, ecx
 dec eax
 mov ebp, 0x4
 mul ebp
 mov esi, dword [esp+0x14]
 mov edi, dword [esp+0x18]
 mov ebp, dword [esp+0x1c]
 add esi, eax
 add edi, eax

 .x47d470:
 mov eax, dword [esi]
 mul ebx
 add eax, ebp
 adc edx, 0x0
 mov dword [edi], eax
 mov ebp, edx
 sub esi, 0x4
 sub edi, 0x4
 dec ecx
 jne .x47d470

 .x47d486:
 mov eax, ebp
 pop ebx
 pop edi
 pop esi
 pop ebp
 retn 0xc


x47d490:
 push ebx
 mov ebx, dword [esp+0xc]
 push ebp
 push esi
 push edi
 mov esi, 0x21
 xor edi, edi
 nop 

 .x47d4a0:
 xor edx, edx
 lea eax, [esi+0x7b5]
 mov ecx, 0x34
 div ecx
 mov esi, 0x34
 mov ebp, 0x5
 mov ecx, edx
 xor edx, edx
 lea eax, [ecx+0x7b5]
 div esi
 mov esi, edx
 mov edx, dword [esp+0x14]
 movzx eax, byte [edi+edx]
 movzx eax, byte [eax+0x51ea70]
 cdq 
 idiv ebp
 inc edi
 cmp edi, 0x1a
 mov byte [ecx+ebx], al
 mov byte [esi+ebx], dl
 jb .x47d4a0

 .x47d4e5:
 pop edi
 pop esi
 pop ebp
 pop ebx
 retn 


x47d920:
 mov eax, dword [esp+0x4]
 sub esp, 0x44
 test eax, eax
 je .x47d9e3

 .x47d9e3:
 add esp, 0x44
 retn 

 .x47d92f:
 push ebx
 mov ebx, dword [esp+0x58]
 test ebx, ebx
 je .x47d9e2

 .x47d9e2:
 pop ebx

 .x47d93c:
 push esi
 push edi
 lea ecx, [esp+0x1c]
 push ecx
 push eax
 call 0x47d490
 xor edx, edx
 mov dword [esp+0x18], edx
 mov dword [esp+0x1c], edx
 mov esi, 0x34
 lea edi, [esp+0x57]
 add esp, 0x8
 mov dword [esp+0xc], 0x0
 mov dword [esp+0x18], edx
 sub edi, esi
 lea ecx, [ecx]

 .x47d970:
 movzx eax, byte [edi+esi]
 push eax
 lea ecx, [esp+0x10]
 mov edx, ecx
 push ecx
 push edx
 mov edx, 0x5
 mov ecx, 0x4
 call 0x47d450
 dec esi
 test esi, esi
 jg .x47d970

 .x47d991:
 lea eax, [esp+0xc]
 push eax
 call 0x47d7c0
 add esp, 0x4
 lea edx, [esp+0xc]
 call 0x47d4f0
 mov eax, dword [esp+0xc]
 mov edx, dword [esp+0x58]
 mov ecx, eax
 shr ecx, 0xa
 mov dword [edx], ecx
 mov ecx, dword [esp+0x10]
 and eax, 0x3ff
 mov edx, ecx
 shl eax, 0x10
 shr edx, 0x10
 or eax, edx
 mov edx, dword [esp+0x5c]
 mov dword [edx], eax
 mov eax, dword [esp+0x14]
 mov word [ebx], cx
 mov ecx, dword [esp+0x18]
 pop edi
 mov dword [ebx+0x2], eax
 mov dword [ebx+0x6], ecx
 pop esi


