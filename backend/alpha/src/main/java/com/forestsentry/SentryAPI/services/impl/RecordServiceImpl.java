package com.forestsentry.SentryAPI.services.impl;

import java.util.UUID;
import java.util.List;
import java.util.ArrayList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.stereotype.Service;

import com.forestsentry.SentryAPI.models.dtos.RecordDTO;
import com.forestsentry.SentryAPI.models.entities.Record;
import com.forestsentry.SentryAPI.repositories.RecordRepository;
import com.forestsentry.SentryAPI.services.dec.RecordService;

@Service
public class RecordServiceImpl implements RecordService{

    @Autowired
    private RecordRepository recordRepository;

    @Override
    public Boolean save(RecordDTO dto) throws Exception{
        try{
            Record r = new Record(dto);
            recordRepository.save(r);
            return true;
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Boolean delete(UUID id) throws Exception{
        try{
            recordRepository.deleteById(id);
            return true;
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Record findLatest() throws Exception{
        try{
            return recordRepository.findFirstByOrderByTimestampDesc();
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Record findById(UUID id) throws Exception{
        try{
            return recordRepository.findById(id).orElseThrow();
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public Page<Record> findByDeviceId(String id, Integer page, Integer size) throws Exception{
        try{
            Pageable pageable = PageRequest.of(page, size);
            return recordRepository.findAllByDeviceIDOrderByTimestampDesc(id, pageable);
        }
        catch(Exception e){
            throw e;
        }
    }

    @Override
    public List<Record> findLatestByDeviceId(List<String> ids) throws Exception{
        try{
            List<Record> l = new ArrayList<Record>();
            ids.forEach(id -> {
                l.add(recordRepository.findFirstByDeviceID(id));
            });
            return l;
        }
        catch(Exception e){
            throw e;
        }
    }
    
}